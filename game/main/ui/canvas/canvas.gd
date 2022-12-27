extends TextureRect
class_name SandCanvas
@tool
# Draws data from the simulation onto an image for display

@export var background_colors: Array[Color]
@export var px_scale: int = 3
@export var element_folder_path: String = "res://main/element_visuals/"
@export var element_materials: Array[ElementVisual] = []

var released := true
var start_draw: Vector2
var end_draw: Vector2

var flat_params: Array[Vector3]
var bg_idx: int

signal mouse_pressed(start, end)

func initialize_elements() -> void:
	element_materials = []
	var dir: DirAccess = DirAccess.open(element_folder_path)
	for file in dir.get_files():
		if not file.contains(".tres"):
			continue
		element_materials.append(ResourceLoader.load("%s/%s" % [dir.get_current_dir(), file]))

func _ready() -> void:
	# initialize_elements()
	material = ShaderMaterial.new()
	material.shader = preload("res://main/ui/canvas/element_painter.gdshader")
	texture = ImageTexture.new()
	resized.connect(_resized)
	
	# First, we make arrays to keep track of where each element is located in the category arrays
	var fluid_ids := []
	var flat_ids := []
	var gradient_ids := []
	var metal_ids := []
	
	for _i in range(256):
		fluid_ids.append(0)
		flat_ids.append(0)
		gradient_ids.append(0)
		metal_ids.append(0)
	
	# Left-most empty index of each category of arrays
	var fid := 0
	var aid := 0
	var gid := 0
	var mid := 0
	
	# Initialize the array for each parameter, for each category
	var fluid_params := []
	flat_params = [] # Keep flat params as an instance variable so we can change the background color at runtime
	var gradient_params := []
	var metal_params := []
	
	for _i in range(14):
		var param := []
		for _j in range(24):
			param.append(0)
		fluid_params.append(param)
	
	for _i in range(24):
		flat_params.append(Vector3())
	
	for _i in range(8):
		var param := []
		for _j in range(32):
			param.append(Vector3())
		gradient_params.append(param)
	
	for _i in range(2):
		var param := []
		for _j in range(24):
			param.append(Vector3())
		metal_params.append(param)
	
	# Load the arrays from data in each resource
	for mat in element_materials:
		if mat is Fluid:
			fluid_params[0][fid] = mat.noise_scale
			fluid_params[1][fid] = mat.noise_speed
			fluid_params[2][fid] = mat.current_size
			fluid_params[3][fid] = mat.wave_cycle
			fluid_params[4][fid] = mat.contraction_size
			fluid_params[5][fid] = mat.wave_density
			fluid_params[6][fid] = mat.shimmer_speed
			fluid_params[7][fid] = mat.shimmer_density
			fluid_params[8][fid] = mat.shimmer_opacity
			fluid_params[9][fid] = mat.shimmer_cycle
			# A bug in godot 4 beta 9 doesn't allow for Colors to be passed as parameters
			fluid_params[10][fid] = Vector3(mat.color_a.r, mat.color_a.g, mat.color_a.b)
			fluid_params[11][fid] = Vector3(mat.color_b.r, mat.color_b.g, mat.color_b.b)
			fluid_params[12][fid] = Vector3(mat.color_c.r, mat.color_c.g, mat.color_c.b)
			fluid_params[13][fid] = mat.noise_texture
			fid += 1
			fluid_ids[mat.id] = fid 
		if mat is FlatColor:
			flat_params[aid] = Vector3(mat.color.r, mat.color.g, mat.color.b)
			aid += 1
			flat_ids[mat.id] = aid
			if mat.id == 0:
				bg_idx = aid - 1
		if mat is GradientColor:
			gradient_params[0][gid] = Vector3(mat.color_a.r, mat.color_a.g, mat.color_a.b)
			gradient_params[1][gid] = Vector3(mat.color_b.r, mat.color_b.g, mat.color_b.b)
			gradient_params[2][gid] = Vector3(mat.color_c.r, mat.color_c.g, mat.color_c.b)
			gradient_params[3][gid] = Vector3(mat.color_d.r, mat.color_d.g, mat.color_d.b)
			gradient_params[4][gid] = Vector3(mat.color_e.r, mat.color_e.g, mat.color_e.b)
			gradient_params[5][gid] = mat.offset_1
			gradient_params[6][gid] = mat.offset_2
			gradient_params[7][gid] = mat.offset_3
			gid += 1
			gradient_ids[mat.id] = gid 
		if mat is Metal:
			metal_params[0][mid] = Vector3(mat.color_a.r, mat.color_a.g, mat.color_a.b)
			metal_params[1][mid] = Vector3(mat.color_b.r, mat.color_b.g, mat.color_b.b)
			mid += 1
			metal_ids[mat.id] = mid 
	# Load all the values into the shader
	get_material().set_shader_parameter("fluid_id_match", fluid_ids)
	get_material().set_shader_parameter("flat_color_id_match", flat_ids)
	get_material().set_shader_parameter("gradient_id_match", gradient_ids)
	get_material().set_shader_parameter("metal_id_match", metal_ids)
	
	get_material().set_shader_parameter("noise_scale", fluid_params[0])
	get_material().set_shader_parameter("noise_speed", fluid_params[1])
	get_material().set_shader_parameter("current_size", fluid_params[2])
	get_material().set_shader_parameter("wave_cycle", fluid_params[3])
	get_material().set_shader_parameter("contraction_size", fluid_params[4])
	get_material().set_shader_parameter("wave_density", fluid_params[5])
	get_material().set_shader_parameter("shimmer_speed", fluid_params[6])
	get_material().set_shader_parameter("shimmer_density", fluid_params[7])
	get_material().set_shader_parameter("shimmer_opacity", fluid_params[8])
	get_material().set_shader_parameter("shimmer_cycle", fluid_params[9])
	get_material().set_shader_parameter("color_a", fluid_params[10])
	get_material().set_shader_parameter("color_b", fluid_params[11])
	get_material().set_shader_parameter("color_c", fluid_params[12])
	get_material().set_shader_parameter("noise_texture", fluid_params[13])
	
	get_material().set_shader_parameter("flat_color", flat_params)
	
	get_material().set_shader_parameter("gradient_color_a", gradient_params[0])
	get_material().set_shader_parameter("gradient_color_b", gradient_params[1])
	get_material().set_shader_parameter("gradient_color_c", gradient_params[2])
	get_material().set_shader_parameter("gradient_color_d", gradient_params[3])
	get_material().set_shader_parameter("gradient_color_e", gradient_params[4])
	get_material().set_shader_parameter("gradient_offset_1", gradient_params[5])
	get_material().set_shader_parameter("gradient_offset_2", gradient_params[6])
	get_material().set_shader_parameter("gradient_offset_3", gradient_params[7])
	
	get_material().set_shader_parameter("metal_color_a", metal_params[0])
	get_material().set_shader_parameter("metal_color_b", metal_params[1])
	
	# We have to initialize these things on a new material since godot 4 beta 9 crashes with uniform arrays :(
	get_material().set_shader_parameter("water_texture", preload("res://main/element_visuals/textures/water_noise.png"))
	get_material().set_shader_parameter("fire_texture", preload("res://main/element_visuals/textures/fire_noise.jpg"))
	get_material().set_shader_parameter("crystal_texture", preload("res://main/element_visuals/textures/crystal.jpg"))

func _resized() -> void:
	get_material().set_shader_parameter("width", size.x)
	get_material().set_shader_parameter("height", size.y)
	get_material().set_shader_parameter("px_scale", px_scale)

func _process(_delta: float) -> void:
	if Input.is_action_just_released("screen_press"):
		released = true
	elif Input.is_action_pressed("screen_press"):
		if released:
			start_draw = get_viewport().get_mouse_position() / px_scale
			released = false
			mouse_pressed.emit(start_draw, start_draw)
		else:
			end_draw = get_viewport().get_mouse_position() / px_scale
			mouse_pressed.emit(start_draw, end_draw)
			start_draw = end_draw

func repaint(sim: SandSimulation) -> void:
	# The simulation stores a single byte for each element, so we can use the luminosity format
	# to save space
	if sim.get_width() <= 0 or sim.get_height() <= 0:
		return
	texture.set_image(Image.create_from_data(sim.get_width(), sim.get_height(), false, Image.FORMAT_L8, sim.get_draw_data()))

func set_background_color(col: Color) -> void:
	flat_params[bg_idx] = Vector3(col.r, col.g, col.b)
	get_material().set_shader_parameter("flat_color", flat_params)

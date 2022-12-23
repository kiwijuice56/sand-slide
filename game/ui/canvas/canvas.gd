extends TextureRect
class_name SandCanvas
@tool

# Draws data from the simulation onto an image for display

@export var px_scale: int = 4
@export var element_folder_path: String = "res://ui/canvas/elements/"
@export var element_materials: Array[ElementVisual] = []

signal mouse_pressed(row, col, is_left)

func initialize_elements() -> void:
	element_materials = []
	var dir: DirAccess = DirAccess.open(element_folder_path)
	for file in dir.get_files():
		if not file.contains(".tres"):
			continue
		element_materials.append(ResourceLoader.load("%s/%s" % [dir.get_current_dir(), file]))

func _ready() -> void:
	#initialize_elements()
	material = ShaderMaterial.new()
	material.shader = preload("res://ui/canvas/element_painter.gdshader")
	texture = ImageTexture.new()
	resized.connect(_resized)
	
	# First, we make arrays to keep track of where each element is located in the category arrays
	var fluid_ids := []
	var flat_ids := []
	var gradient_ids := []
	for _i in range(53):
		fluid_ids.append(0)
		flat_ids.append(0)
		gradient_ids.append(0)
	
	# Left-most empty index of each category of arrays
	var fid := 0
	var aid := 0
	var gid := 0
	
	# Initialize the array for each parameter, for each category
	var fluid_params := []
	var flat_params := []
	var gradient_params := []
	
	for _i in range(14):
		var param := []
		for _j in range(10):
			param.append(0)
		fluid_params.append(param)
	
	for _i in range(54):
		flat_params.append(Vector3())
	
	for _i in range(2):
		var param := []
		for _j in range(19):
			param.append(Vector3())
		gradient_params.append(param)
	
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
		if mat is GradientColor:
			gradient_params[0][gid] = Vector3(mat.color_a.r, mat.color_a.g, mat.color_a.b)
			gradient_params[1][gid] = Vector3(mat.color_b.r, mat.color_b.g, mat.color_b.b)
			gid += 1
			gradient_ids[mat.id] = gid 
	get_material().set_shader_parameter("fluid_id_match", fluid_ids)
	get_material().set_shader_parameter("flat_color_id_match", flat_ids)
	get_material().set_shader_parameter("gradient_id_match", gradient_ids)
	
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
	
	get_material().set_shader_parameter("flat_color", flat_params)
	
	get_material().set_shader_parameter("gradient_color_a", gradient_params[0])
	get_material().set_shader_parameter("gradient_color_b", gradient_params[1])
	
	get_material().set_shader_parameter("water_texture", preload("res://ui/canvas/elements/textures/water_noise.png"))

func _resized() -> void:
	get_material().set_shader_parameter("width", size.x)
	get_material().set_shader_parameter("height", size.y)
	get_material().set_shader_parameter("px_scale", px_scale)

func _process(_delta: float) -> void:
	# Keep track of both mouse buttons so that we can use the left mouse
	# as the draw button and the right mouse as the erase button
	var left_pressed: bool = Input.is_mouse_button_pressed(MOUSE_BUTTON_LEFT)
	var right_pressed: bool = Input.is_mouse_button_pressed(MOUSE_BUTTON_RIGHT)
	if left_pressed or right_pressed:
		var row: int = int(get_viewport().get_mouse_position().y / px_scale)
		var col: int = int(get_viewport().get_mouse_position().x / px_scale)
		mouse_pressed.emit(row, col, left_pressed)

func repaint(sim: SandSimulation) -> void:
	# The simulation stores a single byte for each element, so we can use the luminosity format
	# to save space
	if sim.get_width() <= 0 or sim.get_height() <= 0:
		return
	texture.set_image(Image.create_from_data(sim.get_width(), sim.get_height(), false, Image.FORMAT_L8, sim.get_draw_data()))

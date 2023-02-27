@tool
extends TextureRect
class_name SandCanvas
# Draws data from the simulation onto an image for display

@export var px_scale: int = 3
@export var element_materials: Array[Element] = []

var released := true
var start_draw: Vector2
var end_draw: Vector2

@export var flat_params: Array[Vector3]
var bg_idx: int

signal mouse_pressed(start, end)

# This method is only called in the editor to initialize the list of elements
func _initialize_elements() -> void:
	material = ShaderMaterial.new()
	material.shader = preload("res://main/ui/drawing_panel/canvas/element_painter.gdshader")
	texture = ImageTexture.new()
	element_materials = []
	var dir: DirAccess = DirAccess.open("res://main/element/")
	for file in dir.get_files():
		if not file.contains(".tres"):
			continue
		element_materials.append(ResourceLoader.load("%s/%s" % [dir.get_current_dir(), file]))
		
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
		for _j in range(32):
			param.append(0)
		fluid_params.append(param)
	
	for _i in range(26):
		flat_params.append(Vector3())
	
	for _i in range(8):
		var param := []
		for _j in range(48):
			param.append(Vector3())
		gradient_params.append(param)
	
	for _i in range(2):
		var param := []
		for _j in range(24):
			param.append(Vector3())
		metal_params.append(param)
	
	var fluid_param_names: Array[String] = ["noise_scale", "noise_speed", "current_size", "wave_cycle",
	"contraction_size", "wave_density", "shimmer_speed", "shimmer_density", "shimmer_opacity",
	"shimmer_cycle", "color_a", "color_b", "color_c", "noise_texture"]
	
	var gradient_param_names: Array[String] = ["color_a", "color_b", "color_c",
	"color_d", "color_e", "offset_1", "offset_2", "offset_3"]
	
	# Load the arrays from data in each resource
	for mat in element_materials:
		if mat is Fluid:
			for i in range(len(fluid_param_names)):
				if i >= 10 and i <= 12:
					# A bug in Godot 4 doesn't allow for Colors to be passed as parameters
					fluid_params[i][fid] = Vector3(mat.get(fluid_param_names[i]).r, mat.get(fluid_param_names[i]).g, mat.get(fluid_param_names[i]).b)
				else:
					fluid_params[i][fid] = mat.get(fluid_param_names[i])
			fid += 1
			fluid_ids[mat.id] = fid 
		if mat is FlatColor:
			flat_params[aid] = Vector3(mat.color.r, mat.color.g, mat.color.b)
			aid += 1
			flat_ids[mat.id] = aid
			if mat.id == 0:
				bg_idx = aid - 1
		if mat is GradientColor:
			for i in range(len(gradient_param_names)):
				if i <= 4:
					gradient_params[i][gid] = Vector3(mat.get(gradient_param_names[i]).r, mat.get(gradient_param_names[i]).g, mat.get(gradient_param_names[i]).b)
				else:
					gradient_params[i][gid] = mat.get(gradient_param_names[i])
			gid += 1
			gradient_ids[mat.id] = gid 
		if mat is Metal:
			metal_params[0][mid] = Vector3(mat.color_a.r, mat.color_a.g, mat.color_a.b)
			metal_params[1][mid] = Vector3(mat.color_b.r, mat.color_b.g, mat.color_b.b)
			mid += 1
			metal_ids[mat.id] = mid 
	# Load all of the values into the shader
	get_material().set_shader_parameter("fluid_id_match", fluid_ids)
	get_material().set_shader_parameter("flat_color_id_match", flat_ids)
	get_material().set_shader_parameter("gradient_id_match", gradient_ids)
	get_material().set_shader_parameter("metal_id_match", metal_ids)
	
	for i in range(len(fluid_param_names)):
		get_material().set_shader_parameter(fluid_param_names[i], fluid_params[i])
	
	get_material().set_shader_parameter("flat_color", flat_params)
	
	for i in range(len(gradient_param_names)):
		get_material().set_shader_parameter("gradient_" + gradient_param_names[i], gradient_params[i])
	
	get_material().set_shader_parameter("metal_color_a", metal_params[0])
	get_material().set_shader_parameter("metal_color_b", metal_params[1])
	
	get_material().set_shader_parameter("water_texture", preload("res://main/element/textures/water_noise.png"))
	get_material().set_shader_parameter("fire_texture", preload("res://main/element/textures/fire_noise.jpg"))
	get_material().set_shader_parameter("crystal_texture", preload("res://main/element/textures/crystal.jpg"))
	
	# ResourceSaver.save(get_material(), "res://element_painter.tres")

func _ready() -> void:
	_initialize_elements()
	# The actual canvas does not resize according to size flags due to a bug with texture resizing
	# Instead, a separate canvas is resized properly while this canvas copies its size
	%SizeMirror.resized.connect(_resized)

func _resized() -> void:
	size = %SizeMirror.size
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
	# The simulation stores a single byte for each element, so we can use the luminosity format to save space
	if sim.get_width() <= 0 or sim.get_height() <= 0:
		return
	texture.set_image(Image.create_from_data(sim.get_width(), sim.get_height(), false, Image.FORMAT_L8, sim.get_draw_data()))

func set_background_color(col: Color) -> void:
	flat_params[bg_idx] = Vector3(col.r, col.g, col.b)
	get_material().set_shader_parameter("flat_color", flat_params)

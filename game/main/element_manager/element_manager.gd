extends Node
class_name ElementManager

# Manages custom elements, sending information to the simulation and saving resources

var element_materials: Array[Element]
var element_map: Dictionary

func _ready() -> void:
	await get_tree().get_root().ready
	
	element_materials = []
	var dir: DirAccess = DirAccess.open("res://main/element_manager/element_material")
	for file in dir.get_files():
		# Android devices store resource filenames with the .remap extension.
		# As long as the code provides a valid path, Godot will find the linked resource.
		file = file.replace(".remap", "")
		element_materials.append(ResourceLoader.load("%s/%s" % [dir.get_current_dir(), file]))
	for mat in element_materials:
		element_map[mat.id] = mat
	
	initialize_base_element_graphics()

# Initialize the base elements
func initialize_base_element_graphics() -> void:
	var flat_color: Dictionary = {}
	for mat in element_materials:
		if not mat is FlatColor:
			continue
		flat_color[mat.id] = mat.color.to_rgba32()
	CommonReference.main.sim.initialize_flat_color(flat_color)
	
	var gradient_color: Dictionary = {}
	for mat in element_materials:
		if not mat is GradientColor:
			continue
		gradient_color[mat.id] = [
			mat.color_a.to_rgba32(),
			mat.color_b.to_rgba32(),
			mat.color_c.to_rgba32(),
			mat.color_d.to_rgba32(),
			mat.color_e.to_rgba32(),
			mat.offset_1,
			mat.offset_2,
			mat.offset_3
		]
	CommonReference.main.sim.initialize_gradient_color(gradient_color)
	
	var fluid_color: Dictionary = {}
	for mat in element_materials:
		if not mat is Fluid:
			continue
		fluid_color[mat.id] = [
			mat.color_a.to_rgba32(),
			mat.color_b.to_rgba32(),
			mat.color_c.to_rgba32(),
			mat.noise_texture
		]
	CommonReference.main.sim.initialize_fluid_color(fluid_color)
	var metal_color: Dictionary = {}
	for mat in element_materials:
		if not mat is Metal:
			continue
		metal_color[mat.id] = [
			mat.color_a.to_rgba32(),
			mat.color_b.to_rgba32(),
		]
	CommonReference.main.sim.initialize_metal_color(metal_color)
	
	var images: Array[Image] = [
		load("res://main/element_manager/element_material/textures/water_noise.png").get_image(),
		load("res://main/element_manager/element_material/textures/fire_noise.png").get_image(),
		load("res://main/element_manager/element_material/textures/crystal.png").get_image(),
	]
	CommonReference.main.sim.initialize_textures(images)

func set_background_color(color: Color) -> void:
	element_map[0].color = color
	initialize_base_element_graphics()
	CommonReference.canvas.repaint()

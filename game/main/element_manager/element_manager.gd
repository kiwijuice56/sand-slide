extends Node
class_name ElementManager

# Manages custom elements, sending information to the simulation and saving resources

var element_materials: Array[Element]
var element_map: Dictionary
var custom_element_map: Dictionary

func _ready() -> void:
	Settings.background_updated.connect(set_background_color)
	
	element_materials = []
	var dir: DirAccess = DirAccess.open("res://main/element_manager/element_material")
	for file in dir.get_files():
		# Android devices store resource filenames with the .remap extension.
		# As long as the code provides a valid path, Godot will find the linked resource.
		file = file.replace(".remap", "")
		element_materials.append(ResourceLoader.load("%s/%s" % [dir.get_current_dir(), file]))
	for mat in element_materials:
		element_map[mat.id] = mat
	
	# Load custom element data
	custom_element_map = {}
	dir = DirAccess.open("user://")
	for file in dir.get_files():
		if not file.ends_with(".tres"):
			continue
		if file == "config.tres":
			continue
		var custom_element: CustomElement = ResourceLoader.load("user://" + file)
		custom_element_map[custom_element.id] = custom_element
	
	await get_tree().get_root().ready
	
	initialize_custom_elements()
	set_background_color(Settings.bg_color)

func create_new_element() -> void:
	var id: int = 2048
	while id in custom_element_map:
		id += 1
	if id > 4096:
		print("too many elements!!")
		return
	var new_element: CustomElement = CustomElement.new()
	new_element.id = id
	new_element.display_name = RandomName.NAMES.pick_random()
	new_element.color_a = Color.from_hsv(randf(), randf() * 0.5 + 0.5, randf() * 0.5 + 0.5)
	if randf() < 0.5:
		new_element.style = 0
		new_element.color_b = new_element.color_a
		new_element.color_c = new_element.color_a
	else:
		new_element.style = 1
		new_element.color_b = Color.from_hsv(randf(), randf() * 0.5 + 0.5, randf() * 0.5 + 0.5)
		new_element.color_c = Color.from_hsv(randf(), randf(), randf())
	new_element.state = randi() % 4
	new_element.density = randf()
	new_element.viscosity = randf()
	new_element.conductivity = randf() if randf() < 0.5 else 0.0
	new_element.temperature = randf()
	new_element.flammability = randf() if randf() < 0.5 else 0.0
	new_element.reactivity = randf()
	new_element.durability = randf()
	new_element.power = randf()
	new_element.explosive = randf() < 0.3
	new_element.alive = randf() < 0.3
	new_element.toxic = randf() < 0.3
	new_element.evaporable = randf() < 0.3
	new_element.attractive = randf() < 0.2
	new_element.soluble = randf() < 0.4
	new_element.infectious = randf() < 0.2
	
	var possible_rand: Array = [
		1, 15, 3, 5, 30, 2, 19, 20, 23, 164, 16, 87, 65, 26, 51, 44, 
		82, 133, 17, 45, 70, 163, 162, 158, 132, 33, 11, 21, 136
	]
	new_element.reactant_1 = possible_rand.pick_random()
	new_element.product_1 = possible_rand.pick_random()
	new_element.reactant_2 = possible_rand.pick_random()
	new_element.product_2 = possible_rand.pick_random()
	
	custom_element_map[id] = new_element
	Settings.custom_element_ordering.append(id)
	Settings.save_settings()
	initialize_custom_elements()
	save_elements()

func save_elements() -> void:
	for element in custom_element_map.values():
		ResourceSaver.save(element, "user://" + str(element.id) + element.display_name + ".tres")

func initialize_custom_elements() -> void:
	var pass_dict: Dictionary = {}
	for element in custom_element_map.values():
		var custom_element: CustomElement = element
		pass_dict[custom_element.id] = []
		pass_dict[custom_element.id].append(custom_element.state)
		pass_dict[custom_element.id].append(custom_element.density)
		pass_dict[custom_element.id].append(custom_element.viscosity)
		pass_dict[custom_element.id].append(custom_element.conductivity)
		pass_dict[custom_element.id].append(custom_element.temperature)
		pass_dict[custom_element.id].append(custom_element.flammability)
		pass_dict[custom_element.id].append(custom_element.reactivity)
		pass_dict[custom_element.id].append(custom_element.durability)
		pass_dict[custom_element.id].append(custom_element.power)
		pass_dict[custom_element.id].append(custom_element.explosive)
		pass_dict[custom_element.id].append(custom_element.evaporable)
		pass_dict[custom_element.id].append(custom_element.alive)
		pass_dict[custom_element.id].append(custom_element.toxic)
		pass_dict[custom_element.id].append(custom_element.attractive)
		pass_dict[custom_element.id].append(custom_element.infectious)
		pass_dict[custom_element.id].append(custom_element.soluble)
		pass_dict[custom_element.id].append(custom_element.reactant_1)
		pass_dict[custom_element.id].append(custom_element.product_1)
		pass_dict[custom_element.id].append(custom_element.reactant_2)
		pass_dict[custom_element.id].append(custom_element.product_2)
		pass_dict[custom_element.id].append(custom_element.reactant_3)
		pass_dict[custom_element.id].append(custom_element.product_3)
		
	CommonReference.main.sim.initialize_custom_elements(pass_dict)
	initialize_element_graphics()

func initialize_element_graphics() -> void:
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
		]
	for element in custom_element_map.values():
		fluid_color[element.id] = [
			element.color_a.to_rgba32(),
			element.color_b.to_rgba32(),
			element.color_c.to_rgba32(),
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

func set_background_color(color: Color) -> void:
	element_map[0].color = color
	initialize_element_graphics()
	CommonReference.canvas.repaint()

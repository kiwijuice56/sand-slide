extends Node
class_name ElementManager

# Manages custom elements, sending information to the simulation and saving resources

var element_material_map: Dictionary

func _ready() -> void:
	await get_tree().get_root().ready
	initialize_element_material_map()

# Initialize the base elements
func initialize_element_material_map() -> void:
	var element_materials: Array[Element] = []
	var dir: DirAccess = DirAccess.open("res://main/element_manager/element_material")
	for file in dir.get_files():
		# Android devices store resource filenames with the .remap extension.
		# As long as the code provides a valid path, Godot will find the linked resource.
		file = file.replace(".remap", "")
		element_materials.append(ResourceLoader.load("%s/%s" % [dir.get_current_dir(), file]))
	for element in element_materials:
		element_material_map[element.id] = element
	CommonReference.main.sim.set_element_material_map(element_material_map)

extends Node
class_name Main
# Wrapper class for the cpp Simulation class

var sim: SandSimulation
var element_material_map: Dictionary

var active: bool = false

func initialize_element_material_map() -> void:
	var element_materials: Array[Element] = []
	var dir: DirAccess = DirAccess.open("res://main/element/")
	for file in dir.get_files():
		file = file.replace(".remap", "")
		element_materials.append(ResourceLoader.load("%s/%s" % [dir.get_current_dir(), file]))
	for element in element_materials:
		element_material_map[element.id] = element
	sim.set_element_material_map(element_material_map)

func _ready() -> void:
	sim = SandSimulation.new()
	sim.set_chunk_size(8)
	
	await get_tree().get_root().ready
	CommonReference.canvas.resized.connect(_on_window_resized)
	
	initialize_element_material_map()
	
	_on_window_resized()

func _on_window_resized() -> void:
	sim.resize(int(CommonReference.canvas.size.x / Settings.px_scale), int(CommonReference.canvas.size.y / Settings.px_scale))
	CommonReference.canvas.repaint(sim)

func _process(_delta: float) -> void:
	if active:
		sim.step(Settings.simulation_speed)
		CommonReference.canvas.repaint(sim)


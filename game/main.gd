extends Node
class_name Main
# Contains the main simulation runner

@export var canvas: TextureRect
@export var element_selector: TabContainer
@export var simulation_speed: int = 100000

var sim: SandSimulation

var element: int = 1
var elements = ["Void", "Sand", "Rock", "Water"]

func _ready() -> void:
	canvas.resized.connect(_on_window_resized)
	canvas.mouse_pressed.connect(_on_mouse_pressed)
	element_selector.element_selected.connect(_on_element_selected)
	
	sim = SandSimulation.new()
	_on_window_resized()

func _on_window_resized() -> void:
	sim.resize(int(canvas.size.x / canvas.px_scale), int(canvas.size.y / canvas.px_scale))

func _on_mouse_pressed(row: int, col: int, is_left: bool) -> void:
	draw(row, col, element if is_left else 0, 9)

func _on_element_selected(element_name: String) -> void:
	element = elements.find(element_name)

func _process(delta) -> void:
	sim.step(simulation_speed)
	canvas.repaint(sim)

func draw(center_row: int, center_col: int, draw_element: int,radius: int) -> void:
	for row in range(center_row - radius, center_row + radius):
		for col in range(center_col - radius, center_col + radius):
			if sim.in_bounds(row, col):
				sim.set_cell(row, col, draw_element)

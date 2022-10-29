extends Node
class_name Main
# Contains the main simulation and runs the program

# Keep track of element indices of the simulation to be able comminucate drawing info
const ELEMENT_INDEX = [
	"Void", "Sand", "Rock", "Water", "Polliwog", "Fire", 
	"Smoke", "Algae", "Sand Duck", "Explosion", "Lead Azide",
	"Soil", "Seed", "Germinated Seed", "Grass", "Marble", "Dust",
	"Steel", "Wood", "Ice", "Lava", "Acid", "Acid Gas", "Fairy", 
	"Blue Fire", "Glass", "Laser", "Crystal", "Air", "Black Hole",
	"Oil", "Urchin", "Dragon"]

@export var canvas: TextureRect
@export var element_selector: TabContainer
@export var eraser_button: Button
@export var size_slider: HSlider
@export var speed_slider: HSlider
@export var simulation_speed: int = 100000

var sim: SandSimulation
var brush_size: int = 6
var selected_element: int = 1

func _ready() -> void:
	canvas.resized.connect(_on_window_resized)
	canvas.mouse_pressed.connect(_on_mouse_pressed)
	element_selector.element_selected.connect(_on_element_selected)
	size_slider.value_changed.connect(_on_size_changed)
	speed_slider.value_changed.connect(_on_speed_changed)
	eraser_button.pressed.connect(_on_eraser_selected)
	
	sim = SandSimulation.new()
	_on_window_resized()

func _on_window_resized() -> void:
	sim.resize(int(canvas.size.x / canvas.px_scale), int(canvas.size.y / canvas.px_scale))

func _on_mouse_pressed(row: int, col: int, is_left: bool) -> void:
	draw(row, col, selected_element if is_left else 0, brush_size)

func _on_element_selected(element_name: String) -> void:
	selected_element = ELEMENT_INDEX.find(element_name)

func _on_size_changed(new_brush_size: int) -> void:
	brush_size = new_brush_size

func _on_speed_changed(new_speed: int) -> void:
	simulation_speed = new_speed

func _on_eraser_selected() -> void:
	selected_element = 0

func _notification(what):
	if what == Window.NOTIFICATION_WM_CLOSE_REQUEST or what == Window.NOTIFICATION_WM_GO_BACK_REQUEST:
		set_process(false)
		sim.clean_up()
		get_tree().quit()

func _process(delta) -> void:
	# If we don't limit the delta, the larger step will cause 
	# the next delta to be even higher, causing a loop until the
	# program crashes
	sim.step(int(simulation_speed * min(0.005, delta)))
	canvas.repaint(sim)

# Draw a circle of the element onto the simulation
func draw(center_row: int, center_col: int, draw_element: int, radius: int) -> void:
	if not sim.in_bounds(center_row, center_col):
		return
	for row in range(-radius, radius + 1):
		for col in range(-radius, radius + 1):
			if row*row + col*col < radius*radius and sim.in_bounds(row + center_row, col + center_col):
				# Check if cell is empty when drawing a fluid
				var at_cell: int = sim.get_cell(row + center_row, col + center_col)
				if (draw_element in [3, 5, 20, 21, 24, 28, 30]) and at_cell != 0:
					continue
				sim.set_cell(row + center_row, col + center_col, draw_element)

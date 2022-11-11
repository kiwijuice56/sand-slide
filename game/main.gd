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
	"Oil", "Urchin", "Dragon", "Critter", "Nuclear Explosion", 
	"Uranium", "Neutron", "Lightning", "Plasma", "Electron", "StormPlasma",
	"Hurricane", "Powder", "Liquid Powder", "Mercury", "Potassium",
	"PExplosion"]

@export var save_file_manager: Node
@export var canvas: TextureRect

@export var simulation_speed: int = 100000
@export var chunk_size: int = 8


var sim: SandSimulation
var brush_size: int = 6
var selected_element: int = 1

var draw_enabled: bool = false:
	set(value):
		draw_enabled = value
		var connected: bool = canvas.mouse_pressed.is_connected(_on_mouse_pressed)
		if draw_enabled and not connected:
			canvas.mouse_pressed.connect(_on_mouse_pressed)
		elif connected:
			canvas.mouse_pressed.disconnect(_on_mouse_pressed)

func _ready() -> void:
	canvas.resized.connect(_on_window_resized)
	
	sim = SandSimulation.new()
	sim.set_chunk_size(chunk_size)
	_on_window_resized()

func _on_window_resized() -> void:
	sim.resize(int(canvas.size.x / canvas.px_scale), int(canvas.size.y / canvas.px_scale))
	canvas.repaint(sim)

func _on_mouse_pressed(row: int, col: int, is_left: bool) -> void:
	draw(row, col, selected_element if is_left else 0, brush_size)

# Clean up memory in simulation
func _notification(what):
	if what == Window.NOTIFICATION_WM_CLOSE_REQUEST or what == Window.NOTIFICATION_WM_GO_BACK_REQUEST:
		set_process(false)
		sim.clean_up()
		get_tree().quit()

func _process(_delta) -> void:
	if draw_enabled:
		sim.step(simulation_speed)
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
				if (draw_element in [3, 5, 20, 21, 24, 28, 30, 37, 39, 41, 44]) and at_cell != 0:
					continue
				sim.set_cell(row + center_row, col + center_col, draw_element)

func clear() -> void:
	for i in range(sim.get_height()):
		for j in range(sim.get_width()):
			sim.set_cell(i, j, 0)

func save_image(path: String) -> void:
	canvas.texture.get_image().save_png(path)

func load_image(path: String) -> void:
	clear()
	var img: Image = canvas.texture.get_image().load_from_file(path)
	for i in range(sim.get_height()):
		for j in range(sim.get_width()):
			if j >= img.get_width() or i >= img.get_height():
				continue
			sim.set_cell(i, j, int(255 * img.get_pixel(j, i).r))
	canvas.repaint(sim)

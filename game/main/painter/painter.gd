extends Node
class_name Painter

# Listens for mouse input and draws selected elements onto the simulation grid

# Fluids and powders have different rules when drawing, so we must store which IDs
# belong to each group (initialized in _ready). This method is not so clean, but 
# accessing this information directly from the element classes would require them each to 
# be registered in the Godot class database.
var is_powder: Dictionary = {}
var is_fluid: Dictionary = {}
var is_super_powder: Dictionary = {}

# Reference to the simulation from Main for less verbose access
var sim: SandSimulation

# State variables
var press_released: bool = true
var next_release_invalid: bool = false
var selected_element: int = 1
var start_draw: Vector2
var end_draw: Vector2

signal mouse_pressed(start, end)

func _ready() -> void:
	await get_tree().get_root().ready
	sim = CommonReference.main.sim
	
	for i in [3, 5, 20, 21, 24, 28, 30, 37, 39, 41, 44, 47, 66, 118, 127, 136, 146, 161, 163]:
		is_fluid[i] = true
	for i in [1, 11, 12, 16, 42, 4, 8, 23, 31, 32, 33, 49, 63, 64, 45, 70, 72, 75, 85, 95, 98, 119, 128, 130, 162, 159, 157, 164, 168, 174]:
		is_powder[i] = true
	for i in [175]:
		is_super_powder[i] = true
	mouse_pressed.connect(_on_mouse_pressed)

func _process(_delta: float) -> void:
	if not CommonReference.main.active:
		next_release_invalid = true
		press_released = true
		return
	
	if Input.is_action_just_released("screen_press"):
		press_released = true
		next_release_invalid = false
	elif not next_release_invalid and Input.is_action_pressed("screen_press"):
		if press_released:
			start_draw = get_viewport().get_mouse_position() / Settings.px_scale
			press_released = false
			mouse_pressed.emit(start_draw, start_draw)
		else:
			end_draw = get_viewport().get_mouse_position() / Settings.px_scale
			mouse_pressed.emit(start_draw, end_draw)
			start_draw = end_draw

func clear() -> void:
	for i in range(sim.get_height()):
		for j in range(sim.get_width()):
			sim.draw_cell(i, j, 0)
	# Ensures that the canvas is updated even in the pause menu
	CommonReference.canvas.repaint()

func _on_mouse_pressed(start: Vector2, end: Vector2) -> void:
	if start.distance_to(end) > Settings.brush_size / 2.0:
		var point: Vector2 = start
		var move_dir: Vector2 = (end - start).normalized()
		var step: float = Settings.brush_size / 4.0
		while point.distance_to(end) > step:
			draw_circle(point.x, point.y, int(Settings.brush_size / 2.0))
			point += move_dir * step
	# Drawing a circle at the end makes the lines rounded
	draw_circle(end.x, end.y, int(Settings.brush_size / 2.0))

func draw_circle(x: float, y: float, radius: float) -> void:
	if not sim.in_bounds(roundi(y), roundi(x)):
		return
	for row in range(-radius, radius + 1):
		for col in range(-radius, radius + 1):
			if row*row + col*col < radius*radius:
				draw_pixel(row + y, col + x)

func draw_pixel(row: float, col: float) -> void:
	# Powders must have some random noise in order to prevent stacking behavior
	if selected_element in is_powder and randf() > 0.1:
		return
	if selected_element in is_super_powder and randf() > 0.01:
		return
	
	var y: int = roundi(row)
	var x: int = roundi(col)
	if not sim.in_bounds(y, x):
		return
	
	var at: int = sim.get_cell(y, x)
	
	# Do not allow fluids to be drawn over solids, unless its fire over vapor/smoke
	if selected_element in is_fluid and not at == 0:
		if not ((selected_element == 5 or selected_element == 24) and (at == 6 or at == 58 or at == 87)):
			return 
	
	# Some elements are internally represented by more than one ID, so we shuffle them 
	if selected_element in [42, 63, 64]:
		selected_element = [42, 63, 64][randi() % 3]
	if selected_element in [75, 76, 77]:
		selected_element = [75, 76, 77][randi() % 3]
	if selected_element in [137, 138, 139]:
		selected_element = [137, 138, 139][randi() % 3]
	
	sim.draw_cell(y, x, selected_element)

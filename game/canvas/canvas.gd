extends TextureRect
class_name SandCanvas

@export var px_scale: int = 3 

signal image_resized
signal mouse_pressed(row, col, is_left)

func _ready() -> void:
	resized.connect(_on_control_resized)
	_on_control_resized()

func _process(_delta: float) -> void:
	var left_pressed: bool = Input.is_mouse_button_pressed(MOUSE_BUTTON_LEFT)
	var right_pressed: bool = Input.is_mouse_button_pressed(MOUSE_BUTTON_RIGHT)
	if left_pressed or right_pressed:
		var row: int = int(get_viewport().get_mouse_position().y / px_scale)
		var col: int = int(get_viewport().get_mouse_position().x / px_scale)
		mouse_pressed.emit(row, col, left_pressed)

func _on_control_resized() -> void:
	resize(int(size.x / px_scale), int(size.y / px_scale))
	image_resized.emit()

func resize(width: int, height: int) -> void:
	# Initialize a blank screen
	var image = Image.load_from_file("res://icon.png")
	image.resize(width, height)
	for row in range(height):
		for col in range(width):
			image.set_pixel(col, row, Color("000"))
	texture = ImageTexture.create_from_image(image)

func reset(sim: SandSimulation) -> void:
	var image: Image = texture.get_image()
	for row in range(sim.get_height()):
		for col in range(sim.get_width()):
			image.set_pixel(col, row, Color("%02d0000" % (sim.get_cell(row, col))))
	texture.set_image(image)

func repaint(sim: SandSimulation, modified: Dictionary) -> void:
	var image: Image = texture.get_image()
	
	for cell in sim.get_modified_cells():
		var row: int = floor(cell / sim.get_width())
		var col: int = cell % sim.get_width()
		image.set_pixel(col, row, Color("%02d0000" % (sim.get_cell(row, col))))
	texture.set_image(image)

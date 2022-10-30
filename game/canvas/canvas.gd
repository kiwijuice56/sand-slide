extends TextureRect
class_name SandCanvas
# Draws data from the simulation onto an image for display

@export var px_scale: int = 4

signal mouse_pressed(row, col, is_left)

func _ready() -> void:
	var image = Image.new()
	image.create(256, 256, false, Image.FORMAT_BPTC_RGBA)
	texture = ImageTexture.create_from_image(image)

func _process(_delta: float) -> void:
	# Keep track of both mouse buttons so that we can use the left mouse
	# as the draw button and the right mouse as the erase button
	var left_pressed: bool = Input.is_mouse_button_pressed(MOUSE_BUTTON_LEFT)
	var right_pressed: bool = Input.is_mouse_button_pressed(MOUSE_BUTTON_RIGHT)
	if left_pressed or right_pressed:
		var row: int = int(get_viewport().get_mouse_position().y / px_scale)
		var col: int = int(get_viewport().get_mouse_position().x / px_scale)
		mouse_pressed.emit(row, col, left_pressed)

func repaint(sim: SandSimulation) -> void:
	var image: Image = texture.get_image()
	# The simulation stores a single byte for each element, so we can use the luminosity format
	# to save space
	image.create_from_data(sim.get_width(), sim.get_height(), false, Image.FORMAT_L8, sim.get_draw_data())
	texture.set_image(image)

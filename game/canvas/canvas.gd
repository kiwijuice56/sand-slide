extends TextureRect
class_name SandCanvas

@export var px_scale: int = 3 

signal mouse_pressed(row, col, is_left)

func _ready() -> void:
	var image = Image.load_from_file("res://icon.png")
	texture = ImageTexture.create_from_image(image)

func _process(_delta: float) -> void:
	var left_pressed: bool = Input.is_mouse_button_pressed(MOUSE_BUTTON_LEFT)
	var right_pressed: bool = Input.is_mouse_button_pressed(MOUSE_BUTTON_RIGHT)
	if left_pressed or right_pressed:
		var row: int = int(get_viewport().get_mouse_position().y / px_scale)
		var col: int = int(get_viewport().get_mouse_position().x / px_scale)
		mouse_pressed.emit(row, col, left_pressed)

func repaint(sim: SandSimulation) -> void:
	var image: Image = texture.get_image()
	image.create_from_data(sim.get_width(), sim.get_height(), false, Image.FORMAT_L8, sim.get_draw_data())
#	image.create_from_data()
#	for cell in sim.get_modified_cells():
#		var row: int = floor(cell / sim.get_width())
#		var col: int = cell % sim.get_width()
#		image.set_pixel(col, row, Color("%02d0000" % (sim.get_cell(row, col))))
	texture.set_image(image)

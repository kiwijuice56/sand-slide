extends TextureRect
class_name Canvas

@export var px_scale: int = 3

func _ready() -> void:
	%SizeCopy.resized.connect(_on_resized)

func _on_resized() -> void:
	size = %SizeCopy.size

func repaint() -> void:
	var width: int = CommonReference.main.sim.get_width()
	var height: int = CommonReference.main.sim.get_height()
	if width <= 0 or height <= 0:
		return
	var data: PackedByteArray = CommonReference.main.sim.get_color_image(Settings.flat_mode)
	texture.set_image(Image.create_from_data(width, height, false, Image.FORMAT_RGB8, data))

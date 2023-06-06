extends TextureRect
class_name Canvas

@export var px_scale: int = 3

func repaint(sim: SandSimulation) -> void:
	# The simulation stores a single byte for each element, so we can use the luminosity format to save space
	if sim.get_width() <= 0 or sim.get_height() <= 0:
		return
	texture.set_image(Image.create_from_data(sim.get_width(), sim.get_height(), false, Image.FORMAT_L8, sim.get_color_image()))

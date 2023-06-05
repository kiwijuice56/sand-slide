@tool
extends TextureRect
class_name SandCanvas
# Draws data from the simulation onto an image for display

@export var px_scale: int = 3
@export var element_materials: Array[Element] = []

var released := true
var start_draw: Vector2
var end_draw: Vector2

signal mouse_pressed(start, end)

# This method is only called in the editor to initialize the list of elements
func _initialize_elements() -> void:
	pass
#	element_materials = []
#	var dir: DirAccess = DirAccess.open("res://main/element/")
#	for file in dir.get_files():
#		if not file.contains(".tres"):
#			continue
#		element_materials.append(ResourceLoader.load("%s/%s" % [dir.get_current_dir(), file]))
#	print(element_materials)

func _ready() -> void:
	_initialize_elements()
	# The actual canvas does not resize according to size flags due to a bug with texture resizing
	# Instead, a separate canvas is resized properly while this canvas copies its size
	%SizeMirror.resized.connect(_resized)

func _resized() -> void:
	size = %SizeMirror.size

func _process(_delta: float) -> void:
	if Input.is_action_just_released("screen_press"):
		released = true
	elif Input.is_action_pressed("screen_press"):
		if released:
			start_draw = get_viewport().get_mouse_position() / px_scale
			released = false
			mouse_pressed.emit(start_draw, start_draw)
		else:
			end_draw = get_viewport().get_mouse_position() / px_scale
			mouse_pressed.emit(start_draw, end_draw)
			start_draw = end_draw

func repaint(sim: SandSimulation) -> void:
	# The simulation stores a single byte for each element, so we can use the luminosity format to save space
	if sim.get_width() <= 0 or sim.get_height() <= 0:
		return
	texture.set_image(Image.create_from_data(sim.get_width(), sim.get_height(), false, Image.FORMAT_L8, sim.get_color_image()))

#TODO: reimplement with new graphics
func set_background_color(col: Color) -> void:
	pass

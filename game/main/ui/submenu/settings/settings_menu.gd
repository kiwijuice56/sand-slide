extends Submenu
class_name SettingsMenu
# Handles simulation options

@export var size_slider: HSlider
@export var speed_slider: HSlider
@export var zoom_slider: HSlider
@export var clear_button: Button

var selected_panel: SaveFilePanel

func _ready() -> void:
	disable_components()
	back_button.pressed.connect(_on_back_selected)
	size_slider.value_changed.connect(_on_size_changed)
	speed_slider.value_changed.connect(_on_speed_changed)
	zoom_slider.value_changed.connect(_on_zoom_changed)
	clear_button.pressed.connect(_on_clear_selected)

func _on_size_changed(new_brush_size: int) -> void:
	simulation.brush_size = new_brush_size

func _on_speed_changed(new_speed: int) -> void:
	simulation.simulation_speed = new_speed

func _on_zoom_changed(new_zoom: int) -> void:
	simulation.canvas.px_scale = new_zoom
	simulation.canvas.resized.emit()

func _on_clear_selected() -> void:
	simulation.clear()

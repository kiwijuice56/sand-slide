extends Submenu
class_name SettingsMenu
# Submenu for simulation settings

var selected_panel: SaveFilePanel

func _ready() -> void:
	disable_components()
	back_button.pressed.connect(_on_back_selected)
	%SizeSlider.value_changed.connect(_on_size_changed)
	%SpeedSlider.value_changed.connect(_on_speed_changed)
	%ZoomSlider.value_changed.connect(_on_zoom_changed)
	%ClearButton.pressed.connect(simulation.clear)
	%BackgroundPicker.color_changed.connect(simulation.canvas.set_background_color)

func _on_size_changed(new_brush_size: int) -> void:
	simulation.brush_size = new_brush_size

func _on_speed_changed(new_speed: int) -> void:
	simulation.simulation_speed = new_speed

func _on_zoom_changed(new_zoom: int) -> void:
	simulation.canvas.px_scale = new_zoom
	simulation.canvas.get_material().set_shader_parameter("px_scale", new_zoom)
	simulation.canvas.resized.emit()

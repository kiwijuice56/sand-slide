extends Submenu
class_name SettingsMenu
# Submenu for simulation settings

var selected_panel: SaveFilePanel

func _ready() -> void:
	await get_tree().get_root().ready
	disable_components()
	
	back_button.pressed.connect(_on_back_selected)
	%SizeSlider.value_changed.connect(_on_size_changed)
	%SpeedSlider.value_changed.connect(_on_speed_changed)
	%ZoomSlider.value_changed.connect(_on_zoom_changed)
	%ClearButton.pressed.connect(CommonReference.painter.clear)
	%CheckButton.toggled.connect(_on_mode_changed)
	%BackgroundPicker.color_changed.connect(CommonReference.element_manager.set_background_color)

func _on_size_changed(new_brush_size: int) -> void:
	Settings.brush_size = new_brush_size

func _on_speed_changed(new_speed: int) -> void:
	Settings.simulation_speed = new_speed

func _on_zoom_changed(new_zoom: int) -> void:
	Settings.px_scale = new_zoom
	CommonReference.canvas.resized.emit()

func _on_mode_changed(pressed: bool) -> void:
	Settings.flat_mode = pressed
	CommonReference.canvas.repaint()

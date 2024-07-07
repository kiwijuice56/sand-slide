extends Submenu
class_name SettingsMenu
# Submenu for simulation settings

var selected_panel: SaveFilePanel

func _ready() -> void:
	visible = false
	modulate.a = 0
	await get_tree().get_root().ready
	disable_components()
	
	back_button.pressed.connect(_on_back_selected)
	%SizeSlider.value_changed.connect(_on_size_changed)
	%SpeedSlider.value_changed.connect(_on_speed_changed)
	%ZoomSlider.value_changed.connect(_on_zoom_changed)
	%ClearButton.pressed.connect(CommonReference.painter.clear)
	%CheckButton.toggled.connect(_on_mode_changed)
	%FpsButton.toggled.connect(_on_fps_changed)
	%BackgroundPicker.color_changed.connect(_on_bg_color_changed)
	
	%SizeSlider.value = Settings.brush_size
	%SpeedSlider.value = Settings.simulation_speed
	%ZoomSlider.value = Settings.px_scale
	%CheckButton.set_pressed_no_signal(Settings.sound_on)
	%FpsButton.set_pressed_no_signal(Settings.fps)
	%BackgroundPicker.color = Settings.bg_color
	
	%BackgroundPicker.child_entered_tree.connect(_on_picker_created)
	
	AudioServer.set_bus_mute(AudioServer.get_bus_index("Master"), not Settings.sound_on)

func _on_picker_created(child: Node) -> void:
	var color_picker: ColorPicker = child.get_child(1, true)
	var c = color_picker.get_children(true)
	while len(c) > 0:
		var x = c.pop_back()
		if "virtual_keyboard_enabled" in x:
			x.virtual_keyboard_enabled = false
		c.append_array(x.get_children(true))
	color_picker.sampler_visible = false
	color_picker.color_modes_visible = false
	color_picker.sliders_visible = false
	color_picker.hex_visible = false
	color_picker.presets_visible = false
	DisplayServer.virtual_keyboard_hide()

func _on_size_changed(new_brush_size: int) -> void:
	Settings.brush_size = new_brush_size

func _on_speed_changed(new_speed: int) -> void:
	Settings.simulation_speed = new_speed

func _on_zoom_changed(new_zoom: int) -> void:
	Settings.px_scale = new_zoom
	CommonReference.canvas.resized.emit()

func _on_mode_changed(_pressed: bool) -> void:
	Settings.sound_on = not Settings.sound_on
	AudioServer.set_bus_mute(AudioServer.get_bus_index("Master"), not Settings.sound_on)

func _on_fps_changed(pressed: bool) -> void:
	Settings.fps = pressed

func _on_bg_color_changed(col: Color) -> void:
	Settings.bg_color = col

func exit() -> void:
	super.exit()
	Settings.save_settings()

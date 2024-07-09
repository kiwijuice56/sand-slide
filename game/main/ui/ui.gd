extends Control
class_name UI

# Handles top level UI components and state

@export var save_control: Submenu
@export var settings_control: Submenu
@export var help_control: Submenu
@export var edit_control: Submenu

@export var save_button: Button
@export var settings_button: Button
@export var help_button: Button
@export var edit_button: Button

var player

func _ready() -> void:
	save_button.pressed.connect(_on_save_selected)
	save_control.exited.connect(_on_save_control_exited)
	
	settings_button.pressed.connect(_on_settings_selected)
	settings_control.exited.connect(_on_settings_control_exited)
	
	help_button.pressed.connect(_on_help_selected)
	help_control.exited.connect(_on_help_control_exited)
	
	edit_button.pressed.connect(_on_edit_selected)
	edit_control.exited.connect(_on_edit_control_exited)
	
	CommonReference.main.active = true
	
	var c = get_children()
	player = AudioStreamPlayer.new()
	add_child(player)
	player.stream = preload("res://main/ui/button_click_sound.mp3")
	player.volume_db = -9
	while len(c) > 0:
		var x = c.pop_back()
		if x is Button:
			x.action_mode = BaseButton.ACTION_MODE_BUTTON_RELEASE
			if x is ElementButton:
				x.pressed_long.connect(_on_button_down)
			else:
				x.pressed.connect(_on_button_down)
			if not x.is_in_group("keep_style"):
				x.set("theme_override_styles/pressed", x.get("theme_override_styles/normal"))
				x.set("theme_override_styles/hover", x.get("theme_override_styles/normal"))
				x.set("action_mode", BaseButton.ActionMode.ACTION_MODE_BUTTON_RELEASE)
		if  x is TabBar:
			x.tab_clicked.connect(_on_button_down)
		c.append_array(x.get_children(true))


func _on_button_down(_x=0):
	player.pitch_scale = 1.0 + 0.2 * randf() - 0.1
	player.playing = true

func _on_edit_selected() -> void:
	CommonReference.main.active = false
	var id: int = CommonReference.painter.selected_element
	if id >= 4097:
		id -= 4097
	edit_control.edit_element(CommonReference.element_manager.custom_element_map[id])
	edit_control.enter()

func _on_edit_control_exited() -> void:
	CommonReference.main.active = true
	edit_control.save_changes()
	%ElementSelector.update_custom_elements()
	Settings.save_settings()
	CommonReference.element_manager.save_elements()
	CommonReference.element_manager.initialize_custom_elements()

func _on_save_selected() -> void:
	CommonReference.main.active = false
	save_control.enter()

func _on_save_control_exited() -> void:
	CommonReference.main.active = true

func _on_settings_selected() -> void:
	CommonReference.main.active = false
	settings_control.enter()

func _on_settings_control_exited() -> void:
	CommonReference.main.active = true

func _on_help_selected() -> void:
	CommonReference.main.active = false
	help_control.enter()

func _on_help_control_exited() -> void:
	CommonReference.main.active = true

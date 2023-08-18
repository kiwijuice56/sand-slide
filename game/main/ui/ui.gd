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

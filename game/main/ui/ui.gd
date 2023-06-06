extends Control
class_name UI

# Handles top level UI components and state

@export var save_control: Submenu
@export var settings_control: Submenu
@export var help_control: Submenu

@export var save_button: Button
@export var settings_button: Button
@export var help_button: Button

func _ready() -> void:
	save_button.pressed.connect(_on_save_selected)
	save_control.exited.connect(_on_save_control_exited)
	
	settings_button.pressed.connect(_on_settings_selected)
	settings_control.exited.connect(_on_settings_control_exited)
	
	help_button.pressed.connect(_on_help_selected)
	help_control.exited.connect(_on_help_control_exited)
	
	CommonReference.main.active = true

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

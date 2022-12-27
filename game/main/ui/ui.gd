extends Control
class_name UI
# Handles top level UI components and state

@export var simulation: Main

@export var save_control: Submenu
@export var settings_control: Submenu
@export var help_control: Submenu
@export var splash_screen: ColorRect

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
	
	await splash_screen.intro_complete
	simulation.draw_enabled = true

func _on_save_selected() -> void:
	simulation.draw_enabled = false
	save_control.enter()

func _on_save_control_exited() -> void:
	simulation.draw_enabled = true

func _on_settings_selected() -> void:
	simulation.draw_enabled = false
	settings_control.enter()

func _on_settings_control_exited() -> void:
	simulation.draw_enabled = true

func _on_help_selected() -> void:
	simulation.draw_enabled = false
	help_control.enter()

func _on_help_control_exited() -> void:
	simulation.draw_enabled = true

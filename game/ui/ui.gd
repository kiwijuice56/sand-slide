extends Control
class_name UI
# Handles top level UI components and state

@export var sim_holder: Main

@export var element_selector: TabContainer
@export var save_control: Control
@export var settings_control: Control
@export var splash_screen: ColorRect

@export var eraser_button: Button

@export var save_button: Button
@export var settings_button: Button

func _ready() -> void:
	# Connect to basic UI components
	element_selector.element_selected.connect(_on_element_selected)
	eraser_button.pressed.connect(_on_eraser_selected)
	
	save_button.pressed.connect(_on_save_selected)
	save_control.exited.connect(_on_save_control_exited)
	
	settings_button.pressed.connect(_on_settings_selected)
	settings_control.exited.connect(_on_settings_control_exited)
	
	await splash_screen.intro_complete
	sim_holder.draw_enabled = true

func _on_element_selected(element_name: String) -> void:
	sim_holder.selected_element = sim_holder.ELEMENT_INDEX.find(element_name)

func _on_eraser_selected() -> void:
	sim_holder.selected_element = 0

func _on_save_selected() -> void:
	sim_holder.draw_enabled = false
	save_control.enter()

func _on_save_control_exited() -> void:
	sim_holder.draw_enabled = true

func _on_settings_selected() -> void:
	sim_holder.draw_enabled = false
	settings_control.enter()

func _on_settings_control_exited() -> void:
	sim_holder.draw_enabled = true

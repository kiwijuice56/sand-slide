extends Control
class_name UI
# Handles top level UI components and state

# The Main class
@export var sim_holder: Node

@export var element_selector: TabContainer
@export var save_control: Control

@export var eraser_button: Button
@export var clear_button: Button
@export var save_button: Button

@export var size_slider: HSlider
@export var speed_slider: HSlider
@export var zoom_slider: HSlider

@export var splash_screen: ColorRect

func _ready() -> void:
	# Connect to basic UI components
	element_selector.element_selected.connect(_on_element_selected)
	size_slider.value_changed.connect(_on_size_changed)
	speed_slider.value_changed.connect(_on_speed_changed)
	zoom_slider.value_changed.connect(_on_zoom_changed)
	eraser_button.pressed.connect(_on_eraser_selected)
	clear_button.pressed.connect(_on_clear_selected)
	save_button.pressed.connect(_on_save_selected)
	
	save_control.exited.connect(_on_save_control_exited)
	
	await splash_screen.intro_complete
	sim_holder.draw_enabled = true

func _on_element_selected(element_name: String) -> void:
	sim_holder.selected_element = sim_holder.ELEMENT_INDEX.find(element_name)

func _on_size_changed(new_brush_size: int) -> void:
	sim_holder.brush_size = new_brush_size

func _on_speed_changed(new_speed: int) -> void:
	sim_holder.simulation_speed = new_speed

func _on_zoom_changed(new_zoom: int) -> void:
	sim_holder.canvas.px_scale = new_zoom
	sim_holder.canvas.resized.emit()

func _on_eraser_selected() -> void:
	sim_holder.selected_element = 0

func _on_clear_selected() -> void:
	sim_holder.clear()

func _on_save_selected() -> void:
	sim_holder.draw_enabled = false
	save_control.enter()

func _on_save_control_exited() -> void:
	sim_holder.draw_enabled = true

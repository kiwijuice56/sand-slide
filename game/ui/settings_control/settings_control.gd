extends Control
class_name SettingsControl
# Handles save UI menu and components

signal exited

@export var sim_holder: Main

@export var back_button: Button

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

func _on_back_selected() -> void:
	exit()

func _on_size_changed(new_brush_size: int) -> void:
	sim_holder.brush_size = new_brush_size

func _on_speed_changed(new_speed: int) -> void:
	sim_holder.simulation_speed = new_speed

func _on_zoom_changed(new_zoom: int) -> void:
	sim_holder.canvas.px_scale = new_zoom
	sim_holder.canvas.resized.emit()

func _on_clear_selected() -> void:
	sim_holder.clear()

func enable_components() -> void:
	back_button.disabled = false 

func disable_components() -> void:
	back_button.disabled = true

func enter() -> void:
	$AnimationPlayer.play("enter")
	await $AnimationPlayer.animation_finished
	enable_components()

func exit() -> void:
	disable_components()
	$AnimationPlayer.play("exit")
	await $AnimationPlayer.animation_finished
	exited.emit()

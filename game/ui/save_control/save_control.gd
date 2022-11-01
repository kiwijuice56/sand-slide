extends Control
class_name SaveControl
# Handles save UI menu and components

signal exited

@export var save_button: Button
@export var load_button: Button
@export var back_button: Button

func _ready() -> void:
	disable_components()
	save_button.pressed.connect(_on_save_selected)
	load_button.pressed.connect(_on_load_selected)
	back_button.pressed.connect(_on_back_selected)

func _on_save_selected() -> void:
	pass

func _on_load_selected() -> void:
	pass

func _on_back_selected() -> void:
	exit()

func enable_components() -> void:
	back_button.disabled = false 
	# confirm_button.disabled = false

func disable_components() -> void:
	back_button.disabled = true
	save_button.disabled = true
	load_button.disabled = true

func enter() -> void:
	$AnimationPlayer.play("enter")
	await $AnimationPlayer.animation_finished
	enable_components()

func exit() -> void:
	disable_components()
	$AnimationPlayer.play("exit")
	await $AnimationPlayer.animation_finished
	exited.emit()

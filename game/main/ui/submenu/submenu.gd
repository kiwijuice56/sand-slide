extends Control
class_name Submenu

# Base class for popup menus

signal exited

@export var anim: AnimationPlayer
@export var back_button: Button

func _ready() -> void:
	visible = false
	modulate.a = 0
	disable_components()
	back_button.pressed.connect(_on_back_selected)

func _on_back_selected() -> void:
	exit()

func enable_components() -> void:
	back_button.disabled = false 

func disable_components() -> void:
	back_button.disabled = true

func enter() -> void:
	anim.play("enter")
	await anim.animation_finished
	enable_components()

func exit() -> void:
	disable_components()
	anim.play("exit")
	await anim.animation_finished
	exited.emit()

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

func _notification(notif) -> void:
	notify(notif)

func notify(notif) -> void:
	if visible and notif == NOTIFICATION_WM_GO_BACK_REQUEST:
		_on_back_selected()

func enable_components() -> void:
	back_button.disabled = false 

func disable_components() -> void:
	back_button.disabled = true

func enter() -> void:
	anim.play("enter")
	await anim.animation_finished
	enable_components()

func exit() -> void:
	exited.emit.call_deferred()
	disable_components()
	anim.play("exit")
	await anim.animation_finished
	visible = false
	

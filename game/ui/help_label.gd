extends Label
class_name HelpLabel

@export var canvas: TextureRect

func _ready() -> void:
	canvas.mouse_pressed.connect(_on_mouse_pressed)

func _on_mouse_pressed(row: int, col: int, left_pressed: bool) -> void:
	if $AnimationPlayer.is_playing():
		return
	$AnimationPlayer.play("hide")
	await $AnimationPlayer.animation_finished
	queue_free()

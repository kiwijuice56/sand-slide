extends Label
class_name HelpLabel
# Displays intro text

@export var sim_holder: Node
@export var canvas: TextureRect
@export var splash_screen: ColorRect

func _ready() -> void:
	await splash_screen.intro_complete
	canvas.mouse_pressed.connect(_on_mouse_pressed)

func _on_mouse_pressed(row: int, col: int, _left_pressed: bool) -> void:
	if not sim_holder.sim.in_bounds(row, col):
		return
	if $AnimationPlayer.is_playing():
		return
	$AnimationPlayer.play("hide")
	await $AnimationPlayer.animation_finished
	queue_free()

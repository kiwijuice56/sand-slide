extends ColorRect
class_name SplashScreen

signal intro_complete

func _ready() -> void:
	$AnimationPlayer.play("intro")
	await $AnimationPlayer.animation_finished
	intro_complete.emit()

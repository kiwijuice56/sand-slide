extends ColorRect
class_name SplashScreen

signal intro_complete

func _ready() -> void:
	intro_complete.emit()

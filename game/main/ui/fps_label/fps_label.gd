extends Label
class_name FpsLabel

func _ready() -> void:
	$Timer.timeout.connect(_on_update_timeout)

func _on_update_timeout() -> void:
	visible = Settings.fps
	text = "FPS " + str(Engine.get_frames_per_second())

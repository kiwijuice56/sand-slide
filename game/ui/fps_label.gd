extends Label
class_name FpsLabel
# Keeps track of FPS

func _ready() -> void:
	$Timer.timeout.connect(_on_update_timeout)

func _on_update_timeout() -> void:
	text = "FPS " + str(Engine.get_frames_per_second())

func _input(event) -> void:
	if event.is_action_pressed("toggle_fps"):
		visible = not visible

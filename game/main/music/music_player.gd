extends AudioStreamPlayer

func _ready() -> void:
	randomize()
	seek(stream.get_length() * randf())
	var tween: Tween = get_tree().create_tween().set_pause_mode(Tween.TWEEN_PAUSE_PROCESS)
	tween.tween_property(self, "volume_db", 0.0, 4.0)

extends AudioStreamPlayer

func _ready() -> void:
	randomize()
	seek(stream.get_length() * randf())

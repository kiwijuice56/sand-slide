class_name ElementButton
extends Button

@export var id: int
@export_multiline var description: String = ""

var player

func _ready() -> void:
	player = AudioStreamPlayer.new()
	add_child(player)
	player.stream = preload("res://main/ui/sound_ex_machina_Notification_Accept.mp3")
	player.volume_db = -9
	button_down.connect(_on_button_down)

func _on_button_down():
	if id == 0:
		return
	player.pitch_scale = 1.0 + 0.2 * randf() - 0.1
	player.playing = true

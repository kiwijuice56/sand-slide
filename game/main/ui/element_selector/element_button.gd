class_name ElementButton
extends Button

@export var id: int
@export_multiline var description: String = ""

var player
var simple: bool = false
var timer: Timer

var was_pressed: bool = false

signal pressed_long

func _ready() -> void:
	player = AudioStreamPlayer.new()
	add_child(player)
	player.stream = preload("res://main/ui/notification_accept_sound.mp3")
	player.volume_db = -9
	
	button_down.connect(_on_button_down)
	button_up.connect(_on_button_up)

func _on_button_down():
	was_pressed = true
	await get_tree().create_timer(0.2).timeout
	was_pressed = false

func _on_button_up() -> void:
	if not was_pressed:
		return
	pressed_long.emit()
	
	if id == 0 or simple:
		return
	player.pitch_scale = 1.0 + 0.2 * randf() - 0.1
	player.playing = true

extends Node

signal background_updated(col: Color)

var brush_size: int = 16
var px_scale: int = 3
var simulation_speed: int = 3
var flat_mode: bool = false
var sound_on: bool = true
var fps: bool = false
var custom_element_ordering: Array[int]
var bg_color: Color = Color("#355c96"):
	set(val):
		bg_color = val
		background_updated.emit(val)

func _ready() -> void:
	if ResourceLoader.exists("user://config.tres"):
		var config: Config = ResourceLoader.load("user://config.tres")
		brush_size = config.brush_size
		px_scale = config.px_scale
		simulation_speed = config.simulation_speed
		flat_mode = config.flat_mode
		sound_on = config.sound_on 
		fps = config.fps
		custom_element_ordering = config.custom_element_ordering
		bg_color = config.bg_color

func save_settings() -> void:
	var config: Config = Config.new()
	config.brush_size = brush_size 
	config.px_scale = px_scale
	config.simulation_speed = simulation_speed
	config.flat_mode = flat_mode
	config.sound_on = sound_on
	config.fps = fps
	config.custom_element_ordering = custom_element_ordering
	config.bg_color = bg_color
	ResourceSaver.save(config, "user://config.tres")

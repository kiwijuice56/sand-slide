extends Node

@onready var main: Main = get_tree().get_root().get_node("Main")
@onready var save_file_manager: SaveFileManager = get_tree().get_root().get_node("Main/%SaveFileManager")
@onready var canvas: Canvas = get_tree().get_root().get_node("Main/%Canvas")
@onready var painter: Painter = get_tree().get_root().get_node("Main/%Painter")
@onready var element_manager: ElementManager = get_tree().get_root().get_node("Main/%ElementManager")

extends PanelContainer
class_name SaveFilePanel

@export var name_label: Label
@export var date_label: Label
@export var size_label: Label
var file: SaveFile

signal selected()

func _ready() -> void:
	$Button.button_down.connect(_on_pressed)

func _on_pressed() -> void:
	selected.emit()

func initialize(new_file: SaveFile) -> void:
	file = new_file
	name_label.text = file.save_name
	date_label.text = file.date.substr(0, file.date.find("T"))
	size_label.text = "%.2f KB" % [file.size / 1024.0]

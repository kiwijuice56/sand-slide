extends PanelContainer
class_name SaveFilePanel

@export var name_label: Label
@export var date_label: Label
@export var size_label: Label
@export var thumbnail: TextureRect

var file: SaveFile

signal saved
signal loaded
signal deleted
signal selected

func _ready() -> void:
	$Button.button_down.connect(_on_pressed)
	%Save.pressed.connect(_on_saved)
	%Delete.pressed.connect(_on_deleted)
	%Load.pressed.connect(_on_loaded)
	%ButtonContainer.visible = false

func _on_saved() -> void:
	$AudioStreamPlayer.play()
	saved.emit()

func _on_deleted() -> void:
	$AudioStreamPlayer.play()
	deleted.emit()

func _on_loaded() -> void:
	$AudioStreamPlayer.play()
	loaded.emit()

func _on_pressed() -> void:
	selected.emit()
	$AudioStreamPlayer.play()

func initialize(new_file: SaveFile) -> void:
	file = new_file
	name_label.text = file.save_name
	date_label.text = file.date.substr(0, file.date.find("T"))
	size_label.text = "%.2f KB" % [file.size / 1024.0]
	if not new_file.thumbnail.is_empty():
		var img: Image = new_file.thumbnail
		var texture: ImageTexture = ImageTexture.create_from_image(img)
		thumbnail.texture = texture

extends RichTextLabel

func _ready() -> void:
	meta_clicked.connect(_on_meta_clicked)

func _on_meta_clicked(meta) -> void:
	print(str(meta))
	var data = meta.split(",", true)
	print(OS.shell_open(str(meta)))

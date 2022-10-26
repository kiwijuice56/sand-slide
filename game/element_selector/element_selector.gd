extends TabContainer
class_name ElementSelector

signal element_selected(element_name)

func _ready():
	for scroll_container in get_children():
		for button in scroll_container.get_child(0).get_children():
			button.pressed.connect(_on_button_pressed.bind(button.name))

func _on_button_pressed(button_name: String) -> void:
	element_selected.emit(button_name)

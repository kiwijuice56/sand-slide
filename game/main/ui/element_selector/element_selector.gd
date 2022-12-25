extends TabContainer
class_name ElementSelector
# Handles element selection in the UI

@export var simulation: Main
@export var eraser_button: Button

func _ready():
	eraser_button.pressed.connect(_on_eraser_selected)
	for scroll_container in get_children():
		for button in scroll_container.get_child(0).get_children():
			button.pressed.connect(_on_element_selected.bind(button.name))

func _on_element_selected(element_name: String) -> void:
	simulation.selected_element = simulation.ELEMENT_INDEX.find(element_name)
	# Algae can be different colors!
	if simulation.selected_element == 7:
		simulation.selected_element = [7, 54, 55][randi() % 3]

func _on_eraser_selected() -> void:
	simulation.selected_element = 0

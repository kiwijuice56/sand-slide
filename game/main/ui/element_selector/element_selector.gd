extends TabContainer
class_name ElementSelector
# Handles element selection in the UI

@export var simulation: Main
@export var eraser_button: Button
@export var tap_button: Button

var tap_on := false

func _ready():
	eraser_button.pressed.connect(_on_eraser_selected)
	tap_button.pressed.connect(_on_tap_selected)
	for scroll_container in get_children():
		for button in scroll_container.get_child(0).get_children():
			button.pressed.connect(_on_element_selected.bind(button.name))

func _on_element_selected(element_name: String) -> void:
	tap_button.button_pressed = false
	
	simulation.selected_element = simulation.ELEMENT_INDEX.find(element_name)
	
	# Algae can be different colors!
	if simulation.selected_element == 7:
		simulation.selected_element = [7, 54, 55][randi() % 3]

func _on_eraser_selected() -> void:
	tap_button.button_pressed = false
	simulation.selected_element = 0

func _on_tap_selected() -> void:
	if simulation.selected_element == 0:
		tap_button.button_pressed = false
		return
	
	tap_on = tap_button.button_pressed
	
	simulation.selected_element += 128 if tap_on else -128

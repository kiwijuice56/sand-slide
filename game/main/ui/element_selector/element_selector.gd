extends TabContainer
class_name ElementSelector
# Handles element selection in the UI

@export var simulation: Main
@export var eraser_button: Button
@export var tap_button: Button

var tap_on := false
@export var last_button: Button
@export var selected_material: ShaderMaterial

var gem_idx: int = 0
var algae_idx: int = 0

func _ready() -> void:
	eraser_button.button_down.connect(_on_eraser_selected)
	tap_button.pressed.connect(_on_tap_selected)
	for scroll_container in get_children():
		for button in scroll_container.get_child(0).get_children():
			if not button is Button:
				continue
			button.button_down.connect(_on_element_selected.bind(button))
			for style in ["normal", "pressed", "hover", "disabled"]:
				if not button.get("theme_override_styles/" + style) == null:
					button.get("theme_override_styles/" + style).corner_radius_top_left = 0
					button.get("theme_override_styles/" + style).corner_radius_bottom_left = 0
					button.get("theme_override_styles/" + style).corner_radius_top_right = 0
					button.get("theme_override_styles/" + style).corner_radius_bottom_right = 0

func _on_element_selected(button: ElementButton) -> void:
	tap_button.button_pressed = false
	CommonReference.painter.selected_element = button.id + (4097 if tap_on else 0)
	
	unbolden_button(last_button)
	bolden_button(button)
	last_button = button
	
	# Algae can be different colors!
	if CommonReference.painter.selected_element == 7:
		CommonReference.painter.selected_element = [7, 54, 55][algae_idx]
		algae_idx = (algae_idx + 1) % 3
	
	# Algae can be different colors!
	if CommonReference.painter.selected_element == 27:
		CommonReference.painter.selected_element = [27, 78, 79, 80][gem_idx]
		gem_idx = (gem_idx + 1) % 4

func _on_eraser_selected() -> void:
	if last_button == eraser_button:
		return
	
	bolden_button(eraser_button)
	unbolden_button(last_button)
	unbolden_button(tap_button)
	tap_on = false
	last_button = eraser_button
	CommonReference.painter.selected_element = 0

func _on_tap_selected() -> void:
	if CommonReference.painter.selected_element == 0:
		return
	
	tap_on = !tap_on
	
	if tap_on:
		bolden_button(tap_button)
	else:
		unbolden_button(tap_button)
	
	CommonReference.painter.selected_element += 4097 if tap_on else -4097

func bolden_button(button: Button) -> void:
	if is_instance_valid(button):
		button.material = selected_material

func unbolden_button(button: Button) -> void:
	if is_instance_valid(button):
		button.material = null

class_name ElementPickerButton
extends ElementButton

@export var element_picker: ElementSelector
var current_id: int = -1

func initialize():
	if current_id >= 2048:
		if not current_id in CommonReference.element_manager.custom_element_map:
			current_id = -1
	
	if current_id >= 2048:
		var custom_element: CustomElement = CommonReference.element_manager.custom_element_map[current_id]
		initialize_with_custom(custom_element)
	else:
		initialize_with_basic(current_id)

func initialize_with_custom(element: CustomElement) -> void:
	text = element.display_name.substr(0, 10)
	
	var style: StyleBoxFlat = get("theme_override_styles/normal")
	var new_style: StyleBoxFlat = style.duplicate()
	set("theme_override_styles/normal", new_style)
	new_style.bg_color = element.color_a
	
	style = get("theme_override_styles/hover")
	new_style = style.duplicate()
	set("theme_override_styles/hover", new_style)
	new_style.bg_color = element.color_a.lightened(.35)
	
	style = get("theme_override_styles/pressed")
	new_style = style.duplicate()
	set("theme_override_styles/pressed", new_style)
	new_style.bg_color = element.color_a.darkened(.35)
	
	var c: Color = Color("#000000") if element.color_a.v > 0.75 else Color("#FFFFFF")
	set("theme_override_colors/font_color", c)
	set("theme_override_colors/font_pressed_color", c)
	set("theme_override_colors/font_hover_color", c)
	set("theme_override_colors/font_focus_color", c)
	set("theme_override_colors/font_hover_pressed_color", c)

func initialize_with_basic(id: int) -> void:
	var button: Button = null
	for other_button in element_picker.get_node("%Basic").get_children():
		if other_button.id == id:
			button = other_button
	text = button.text
	
	set("theme_override_styles/normal", button.get("theme_override_styles/normal"))
	set("theme_override_styles/hover", button.get("theme_override_styles/hover"))
	set("theme_override_styles/pressed", button.get("theme_override_styles/pressed"))
	set("theme_override_colors/font_color", button.get("theme_override_colors/font_color"))
	set("theme_override_colors/font_pressed_color",  button.get("theme_override_colors/font_color"))
	set("theme_override_colors/font_hover_color",  button.get("theme_override_colors/font_color"))
	set("theme_override_colors/font_focus_color",  button.get("theme_override_colors/font_color"))
	set("theme_override_colors/font_hover_pressed_color",  button.get("theme_override_colors/font_color"))


func _on_button_down() -> void:
	element_picker.pick_simple(current_id)
	current_id = await element_picker.element_selected
	initialize()

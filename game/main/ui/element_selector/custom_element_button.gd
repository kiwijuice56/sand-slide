class_name CustomElementButton
extends ElementButton

var custom_element: CustomElement 

func initialize(element: CustomElement) -> void:
	custom_element = element
	id = element.id
	
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
	
	
	
	if element.color_a.v > 0.75:
		set("theme_override_colors/font_color", Color("#000000"))
		set("theme_override_colors/font_pressed_color", Color("#000000"))
		set("theme_override_colors/font_hover_color", Color("#000000"))
		set("theme_override_colors/font_focus_color", Color("#000000"))
		set("theme_override_colors/font_hover_pressed_color", Color("#000000"))

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
	set("theme_override_styles/hover", get("theme_override_styles/normal"))
	set("theme_override_styles/pressed", get("theme_override_styles/normal"))
	new_style.bg_color = element.color_a
	
	if element.color_a.v > 0.75:
		set("theme_override_colors/font_color", Color("#000000"))
		set("theme_override_colors/font_pressed_color", Color("#000000"))
		set("theme_override_colors/font_hover_color", Color("#000000"))
		set("theme_override_colors/font_focus_color", Color("#000000"))
		set("theme_override_colors/font_hover_pressed_color", Color("#000000"))

func _on_button_down():
	was_pressed = true
	await get_tree().create_timer(0.2).timeout
	was_pressed = false

func _on_button_up() -> void:
	if not was_pressed:
		return
	pressed_long.emit()
	$AudioStreamPlayer.play()
	
	if id == 0 or simple:
		return
	player.pitch_scale = 1.0 + 0.2 * randf() - 0.1
	player.playing = true

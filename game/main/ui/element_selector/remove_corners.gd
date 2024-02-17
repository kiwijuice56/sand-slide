@tool
extends EditorScript

func _run() -> void:
	for button in get_all_children(get_scene()):
		if not button is ElementButton:
			continue
		# This is a remnant of a past decision to round the corners of some buttons
		# It would be a lot of work to reset it on ALL of the button styles, so 
		# for now it is OK to set it in the script
		for style in ["normal", "pressed", "hover", "disabled"]:
			if not button.get("theme_override_styles/" + style) == null:
				button.get("theme_override_styles/" + style).corner_radius_top_left = 0
				button.get("theme_override_styles/" + style).corner_radius_bottom_left = 0
				button.get("theme_override_styles/" + style).corner_radius_top_right = 0
				button.get("theme_override_styles/" + style).corner_radius_bottom_right = 0
	

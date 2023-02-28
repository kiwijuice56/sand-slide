extends PanelContainer
class_name ElementShowcase

func _ready():
	for button in get_child(0).get_child(0).get_children():
		var i: int = button.get_index()
		for style in ["normal", "pressed", "hover", "disabled"]:
			if not button.get("theme_override_styles/" + style) == null:
				button.get("theme_override_styles/" + style).corner_radius_top_left = 4 if i == 0 else 0
				button.get("theme_override_styles/" + style).corner_radius_bottom_left = 4 if i == 56 else 0
				button.get("theme_override_styles/" + style).corner_radius_top_right = 4 if i == 3 else 0
				button.get("theme_override_styles/" + style).corner_radius_bottom_right = 4 if i == 59 else 0

extends Submenu
class_name ElementEditorMenu
# Submenu for simulation settings

func _ready() -> void:
	for node in get_tree().get_nodes_in_group("color_picker"):
		var color_picker_button: ColorPickerButton = node as ColorPickerButton
		var color_picker: ColorPicker = color_picker_button.get_picker()
		color_picker.sampler_visible = false
		color_picker.color_modes_visible = false
		color_picker.sliders_visible = false
		color_picker.hex_visible = false
		color_picker.presets_visible = false
		print(color_picker)
	#visible = false
	#modulate.a = 0.0

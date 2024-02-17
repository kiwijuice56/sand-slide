class_name ElementPickerButton
extends ElementButton

@export var element_picker: PackedScene

func _on_button_down():
	#super._on_button_down()
	#$AudioStreamPlayer.play()
	
	var picker: ElementSelector = element_picker.instantiate()
	picker.simple = true
	picker.tabs_visible = false
	get_tree().get_root().get_node("Main/CanvasLayer/UI").add_child(picker)


	print(await picker.pick_simple())
	picker.queue_free()

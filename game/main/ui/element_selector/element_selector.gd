extends TabContainer
class_name ElementSelector
# Handles element selection in the UI

const ELEMENT_BUTTON: PackedScene = preload("res://main/ui/element_selector/CustomElementButton.tscn")
const PLACEHOLDER_LABEL: PackedScene = preload("res://main/ui/element_selector/PlaceholderLabel.tscn")

@export var simulation: Main
@export var eraser_button: Button
@export var tap_button: Button

var tap_on: bool = false
@export var last_button: Button
@export var selected_material: ShaderMaterial

@onready var edit_button: Button = get_tree().get_root().get_node("Main").get_node("%Edit")

var gem_idx: int = 0
var algae_idx: int = 0

signal button_pressed(id: int)

var ext_id: int = -1

signal element_selected(id: int)

@export var simple: bool = false

func _ready() -> void:
	if simple:
		last_button = null
	initialize_buttons()
	if not simple:
		%Basic/None.queue_free()
	await get_tree().get_root().ready
	update_custom_elements()

func pick_simple(current_id: int) -> int:
	last_button = null
	ext_id = current_id
	update_custom_elements()
	for button in %Custom.get_children():
		if not button is ElementButton:
			continue
		%Custom.remove_child(button)
		%Basic.add_child(button)
	for button in %Basic.get_children():
		unbolden_button(button)
		if (button.id == current_id):
			bolden_button(button)
	
	$AnimationPlayer.play("in")
	await $AnimationPlayer.animation_finished
	
	var id: int = await button_pressed
	element_selected.emit(id)
	
	$AnimationPlayer.play("out")
	await $AnimationPlayer.animation_finished
	get_parent().visible = false
	
	return id

func _on_new_element_created() -> void:
	CommonReference.element_manager.create_new_element()
	update_custom_elements()

func initialize_buttons() -> void:
	var id: int = -1 if not simple else ext_id
	if is_instance_valid(last_button) and last_button is ElementButton:
		id = last_button.id
	if is_instance_valid(eraser_button) and not eraser_button.pressed.is_connected(_on_eraser_selected):
		eraser_button.pressed.connect(_on_eraser_selected)
	if  is_instance_valid(tap_button) and not tap_button.pressed.is_connected(_on_tap_selected):
		tap_button.pressed.connect(_on_tap_selected)
	if not %CreateNewButton.button_down.is_connected(_on_new_element_created):
		%CreateNewButton.button_down.connect(_on_new_element_created)
	var last_updated: bool = false
	for button in %Basic.get_children() + %Custom.get_children():
		if not button is ElementButton:
			continue
		button.simple = simple
		if not button.pressed_long.is_connected(_on_element_selected):
			button.pressed_long.connect(_on_element_selected.bind(button))
		if button.id == id:
			last_updated = true
			last_button = button
			bolden_button(button)
	if not last_updated and not simple:
		edit_button.visible = false
		CommonReference.painter.selected_element = 0

func update_custom_elements() -> void:
	for child in %Custom.get_children():
		if child.name != "CreateNewButton":
			%Custom.remove_child(child)
			child.queue_free()
	if simple:
		for child in %Basic.get_children():
			if child.id >= 2048:
				%Basic.remove_child(child)
				child.queue_free()
	for element_id in Settings.custom_element_ordering:
		var custom_element: CustomElement = CommonReference.element_manager.custom_element_map[element_id]
		var new_button: CustomElementButton = ELEMENT_BUTTON.instantiate()
		new_button.initialize(custom_element)
		%Custom.add_child(new_button)
	# Fill up the space
	%Custom.move_child(%Custom.get_node("CreateNewButton"), -1)
	for i in range(24 - %Custom.get_child_count()):
		var label: Label = PLACEHOLDER_LABEL.instantiate()
		%Custom.add_child(label)
	initialize_buttons()

func _on_element_selected(button: ElementButton) -> void:
	button_pressed.emit(button.id)
	if simple:
		return
	get_tree().get_root().get_node("Main").get_node("%SelectInfo").show_element(button.text, button.description, button.get("theme_override_styles/normal").bg_color)
	edit_button.visible = button.id >= 2048
	
	tap_button.button_pressed = false
	CommonReference.painter.selected_element = button.id + (4097 if tap_on else 0)
	
	if is_instance_valid(last_button):
		unbolden_button(last_button)
	bolden_button(button)
	last_button = button
	
	# Algae can be different colors!
	if CommonReference.painter.selected_element == 7:
		CommonReference.painter.selected_element = [7, 54, 55][algae_idx]
		algae_idx = (algae_idx + 1) % 3
	
	# Gem can be different colors!
	if CommonReference.painter.selected_element == 27:
		CommonReference.painter.selected_element = [27, 78, 79, 80][gem_idx]
		gem_idx = (gem_idx + 1) % 4

func _on_eraser_selected() -> void:
	edit_button.visible = false
	
	if last_button == eraser_button:
		return
	
	bolden_button(eraser_button)
	if is_instance_valid(last_button):
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

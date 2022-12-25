extends Submenu
class_name SaveFileMenu
# Handles save UI menu and components

@export var save_file_panel: PackedScene

@export var save_file_manager: SaveFileManager

@export var save_file_container: VBoxContainer
@export var save_button: Button
@export var load_button: Button
@export var delete_button: Button
@export var new_file_name: LineEdit

var selected_panel: SaveFilePanel

func _ready() -> void:
	super._ready()
	
	save_button.pressed.connect(_on_save_selected)
	load_button.pressed.connect(_on_load_selected)
	delete_button.pressed.connect(_on_delete_selected)
	new_file_name.text_submitted.connect(_on_text_submitted)
	new_file_name.focus_entered.connect(deselect_panel)

func _on_save_selected() -> void:
	deselect_panel()
	save_file_manager.overwrite_save_file(selected_panel.file)
	refresh_panels()

func _on_load_selected() -> void:
	deselect_panel()
	save_file_manager.load_from_file(selected_panel.file)

func _on_file_selected(panel: SaveFilePanel) -> void:
	selected_panel = panel
	save_button.disabled = false
	load_button.disabled = false
	delete_button.disabled = false

func _on_delete_selected() -> void:
	deselect_panel()
	save_file_manager.delete_save_file(selected_panel.file)
	refresh_panels()

func _on_text_submitted(text: String) -> void:
	deselect_panel()
	save_file_manager.create_save_file(text)
	new_file_name.text = ""
	new_file_name.release_focus()
	refresh_panels()


func disable_components() -> void:
	super.disable_components()
	save_button.disabled = true
	load_button.disabled = true
	delete_button.disabled = true

func enter() -> void:
	refresh_panels()
	super.enter()

func deselect_panel() -> void:
	save_button.disabled = true
	load_button.disabled = true
	delete_button.disabled = true
	if get_viewport().gui_get_focus_owner() is Button:
		get_viewport().gui_get_focus_owner().release_focus()

func refresh_panels() -> void:
	var new_panels: Array[SaveFilePanel] = []
	for file in save_file_manager.files:
		var panel: SaveFilePanel = save_file_panel.instantiate()
		panel.initialize(file)
		new_panels.append(panel)
	for child in save_file_container.get_children():
		child.queue_free()
	for panel in new_panels:
		save_file_container.add_child(panel)
		panel.selected.connect(_on_file_selected.bind(panel))

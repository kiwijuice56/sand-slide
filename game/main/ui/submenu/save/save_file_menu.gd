extends Submenu
class_name SaveFileMenu
# Submenu for saving, loading, creating, and deleting player files

@export var save_file_manager: SaveFileManager
@export var save_file_panel: PackedScene

var selected_panel: SaveFilePanel

func _ready() -> void:
	visible = false
	modulate.a = 0
	super._ready()
	
	%SaveFileButton.pressed.connect(_on_save_selected)
	%LoadFileButton.pressed.connect(_on_load_selected)
	%DeleteFileButton.pressed.connect(_on_delete_selected)
	%FileLabelEdit.text_submitted.connect(_on_text_submitted)
	%FileLabelEdit.focus_entered.connect(deselect_panel)

func _on_save_selected() -> void:
	deselect_panel()
	%SavePlayer.play()
	save_file_manager.overwrite_save_file(selected_panel.file)
	refresh_panels()

func _on_load_selected() -> void:
	deselect_panel()
	save_file_manager.load_from_file(selected_panel.file)
	_on_back_selected()

func _on_file_selected(panel: SaveFilePanel) -> void:
	if is_instance_valid(selected_panel):
		selected_panel.get_node("%ButtonContainer").visible = false
	selected_panel = panel
	selected_panel.get_node("%ButtonContainer").visible = true
	set_buttons_disabled(false)

func _on_delete_selected() -> void:
	deselect_panel()
	%DeletePlayer.play()
	save_file_manager.delete_save_file(selected_panel.file)
	refresh_panels()

func _on_text_submitted(text: String) -> void:
	deselect_panel()
	save_file_manager.create_save_file(text)
	%SavePlayer.play()
	%FileLabelEdit.text = ""
	%FileLabelEdit.release_focus()
	refresh_panels()

func disable_components() -> void:
	super.disable_components()
	set_buttons_disabled(true)

# We may want to disable the main buttons while not disabling all components
func set_buttons_disabled(to_disable: bool) -> void:
	%SaveFileButton.disabled = to_disable
	%LoadFileButton.disabled = to_disable
	%DeleteFileButton.disabled = to_disable

func deselect_panel() -> void:
	set_buttons_disabled(true)
	if is_instance_valid(selected_panel):
		selected_panel.get_node("%ButtonContainer").visible = false
	if get_viewport().gui_get_focus_owner() is Button:
		get_viewport().gui_get_focus_owner().release_focus()

func date_comparison(a: SaveFilePanel, b: SaveFilePanel) -> bool:
	return a.file.time_created > b.file.time_created 

func refresh_panels() -> void:
	var new_panels: Array[SaveFilePanel] = []
	for file in save_file_manager.files:
		var panel: SaveFilePanel = save_file_panel.instantiate()
		panel.initialize(file)
		new_panels.append(panel)
	new_panels.sort_custom(date_comparison)
	for child in %SaveFileContainer.get_children():
		child.queue_free()
	for panel in new_panels:
		%SaveFileContainer.add_child(panel)
		panel.selected.connect(_on_file_selected.bind(panel))
		panel.deleted.connect(_on_delete_selected)
		panel.saved.connect(_on_save_selected)
		panel.loaded.connect(_on_load_selected)

func enter() -> void:
	refresh_panels()
	super.enter()

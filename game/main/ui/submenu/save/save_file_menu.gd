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
	save_file_manager.overwrite_save_file(selected_panel.file)
	refresh_panels()

func _on_load_selected() -> void:
	deselect_panel()
	save_file_manager.load_from_file(selected_panel.file)

func _on_file_selected(panel: SaveFilePanel) -> void:
	selected_panel = panel
	set_buttons_disabled(false)

func _on_delete_selected() -> void:
	deselect_panel()
	save_file_manager.delete_save_file(selected_panel.file)
	refresh_panels()

func _on_text_submitted(text: String) -> void:
	deselect_panel()
	save_file_manager.create_save_file(text)
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
	if get_viewport().gui_get_focus_owner() is Button:
		get_viewport().gui_get_focus_owner().release_focus()

func refresh_panels() -> void:
	var new_panels: Array[SaveFilePanel] = []
	for file in save_file_manager.files:
		var panel: SaveFilePanel = save_file_panel.instantiate()
		panel.initialize(file)
		new_panels.append(panel)
	for child in %SaveFileContainer.get_children():
		child.queue_free()
	for panel in new_panels:
		%SaveFileContainer.add_child(panel)
		panel.selected.connect(_on_file_selected.bind(panel))

func enter() -> void:
	refresh_panels()
	super.enter()

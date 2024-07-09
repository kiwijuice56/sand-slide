extends Submenu
class_name ElementEditorMenu
# Submenu for simulation settings

var current: CustomElement

func _ready() -> void:
	super._ready()
	visible = false
	modulate.a = 0.0
	%Style.item_selected.connect(_on_style_selected)
	%State.item_selected.connect(_on_state_selected)
	%DeleteButton.pressed.connect(_on_element_deleted)
	
	%ColorA.child_entered_tree.connect(_on_picker_created)
	%ColorB.child_entered_tree.connect(_on_picker_created)
	%ColorC.child_entered_tree.connect(_on_picker_created)
	
	%State.get_popup().transparent_bg = true
	%Style.get_popup().transparent_bg = true
	%State.get_popup().transparent_bg = true

func _on_picker_created(child: Node) -> void:
	var color_picker: ColorPicker = child.get_child(1, true)
	var c = color_picker.get_children(true)
	while len(c) > 0:
		var x = c.pop_back()
		if "virtual_keyboard_enabled" in x:
			x.virtual_keyboard_enabled = false
		c.append_array(x.get_children(true))
	color_picker.sampler_visible = false
	color_picker.color_modes_visible = false
	color_picker.sliders_visible = false
	color_picker.hex_visible = false
	color_picker.presets_visible = false
	DisplayServer.virtual_keyboard_hide()

func _on_element_deleted() -> void:
	var dir: DirAccess = DirAccess.open("user://")
	dir.remove(str(current.id) + current.display_name + ".tres")
	
	CommonReference.element_manager.custom_element_map.erase(current.id)
	Settings.custom_element_ordering.remove_at(Settings.custom_element_ordering.find(current.id))
	exit()

func _on_style_selected(idx: int) -> void:
	match idx:
		0:
			%FancyColorGrouping.visible = false
		1:
			%FancyColorGrouping.visible = true

func _on_state_selected(idx: int) -> void:
	%PowerGrouping.visible = false
	%ViscosityGrouping.visible = false
	match idx:
		2:
			%ViscosityGrouping.visible = true
		4:
			%PowerGrouping.visible = true

func edit_element(element: CustomElement) -> void:
	current = element
	initialize()

func initialize() -> void:
	%ScrollContainer.scroll_vertical = 0
	%Name.text = current.display_name
	%Style.selected = current.style
	%ColorA.color = current.color_a
	%ColorB.color = current.color_b
	%ColorC.color = current.color_c
	%State.selected = current.state
	%Density.value = current.density
	%Viscosity.value = current.viscosity
	%Conductivity.value = current.conductivity
	%Temperature.value = current.temperature
	%Flammability.value = current.flammability
	%Reactivity.value = current.reactivity
	%Durability.value = current.durability
	%Power.value = current.power
	%Explosive.button_pressed = current.explosive
	%Alive.button_pressed = current.alive
	%Toxic.button_pressed = current.toxic
	%Evaporable.button_pressed = current.evaporable
	%Attractive.button_pressed = current.attractive
	%Soluble.button_pressed = current.soluble
	%Infectious.button_pressed = current.infectious
	%Reactant1.current_id = current.reactant_1
	%Reactant1.initialize()
	%Product1.current_id = current.product_1
	%Product1.initialize()
	%Reactant2.current_id = current.reactant_2
	%Reactant2.initialize()
	%Product2.current_id = current.product_2
	%Product2.initialize()
	%Reactant3.current_id = current.reactant_3
	%Reactant3.initialize()
	%Product3.current_id = current.product_3
	%Product3.initialize()
	
	_on_state_selected(%State.selected)
	_on_style_selected(%Style.selected)

func save_changes() -> void:
	current.display_name = %Name.text
	current.style = %Style.selected
	current.color_a = %ColorA.color 
	current.color_b = %ColorB.color
	current.color_c = %ColorC.color
	if current.style == 0:
		current.color_b = current.color_a
		current.color_c = current.color_a
	
	current.state = %State.selected 
	current.density = %Density.value 
	current.viscosity = %Viscosity.value
	current.conductivity = %Conductivity.value
	current.temperature = %Temperature.value 
	current.flammability = %Flammability.value
	current.reactivity = %Reactivity.value
	current.durability = %Durability.value
	current.power = %Power.value
	current.explosive = %Explosive.button_pressed
	current.alive = %Alive.button_pressed
	current.toxic = %Toxic.button_pressed
	current.evaporable = %Evaporable.button_pressed
	current.attractive = %Attractive.button_pressed 
	current.soluble = %Soluble.button_pressed 
	current.infectious = %Infectious.button_pressed 
	
	current.reactant_1 = %Reactant1.current_id 
	current.product_1 = %Product1.current_id
	current.reactant_2 = %Reactant2.current_id
	current.product_2 = %Product2.current_id
	current.reactant_3 = %Reactant3.current_id 
	current.product_3 = %Product3.current_id 

func notify(notif) -> void:
	if notif == NOTIFICATION_WM_GO_BACK_REQUEST:
		if %ElementPickerContainer.visible:
			%ElementSelector.button_pressed.emit(%ElementSelector.ext_id)
		elif visible:
			_on_back_selected()

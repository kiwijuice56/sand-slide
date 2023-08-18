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
	
	_on_state_selected(%State.selected)
	_on_style_selected(%Style.selected)

func save_changes() -> void:
	current.display_name =  %Name.text
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

class_name CustomElement
extends Resource

@export var display_name: String
@export var id: int
# 0: flat, 1: fancy
@export var style: int
@export var color_a: Color
@export var color_b: Color
@export var color_c: Color
# 0: powder, 1: solid, 2: liquid, 3: gas
@export var state: int 
@export var density: float = 0.2
@export var viscosity: float = 0.5
@export var conductivity: float = 0.0
@export var temperature: float = 0.5
@export var flammability: float = 0.0
@export var reactivity: float = 0.5
@export var durability: float = 0.5
@export var power: float = 0.5

@export var explosive: bool = false
@export var evaporable: bool = false
@export var alive: bool = false
@export var toxic: bool = false
@export var attractive: bool = false
@export var infectious: bool = false
@export var soluble: bool = false

@export var reactant_1: int = -1
@export var product_1: int = -1

@export var reactant_2: int = -1
@export var product_2: int = -1

@export var reactant_3: int = -1
@export var product_3: int = -1


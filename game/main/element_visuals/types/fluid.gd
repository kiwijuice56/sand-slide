extends ElementVisual
class_name Fluid

@export_enum(WATER, FIRE, CRYSTAL) var noise_texture: int
@export var color_a: Color
@export var color_b: Color
@export var color_c: Color

@export var noise_scale: float = 2.0
@export var noise_speed: float = 15.0
@export var current_size: float = 16.0
@export var wave_cycle: float = 3.0
@export var contraction_size: float = 16.0
@export var wave_density: float = 2.0
@export var shimmer_speed: float = 24.0
@export var shimmer_density: float = 1.5
@export var shimmer_opacity: float = 0.5
@export var shimmer_cycle: float = 2.0

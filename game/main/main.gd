extends Node
class_name Main
# Contains the sand simulation and acts as the root of the game

# Keep track of the indices of each element so that this node can draw it into the simulation
const ELEMENT_INDEX = [
	"Void", "Sand", "Rock", "Water", "Polliwog", "Fire", 
	"Smoke", "Algae", "Sand Duck", "Explosion", "Lead Azide",
	"Soil", "Seed", "Germinated Seed", "Grass", "Wall", "Dust",
	"Iron", "Wood", "Ice", "Lava", "Acid", "Acid Gas", "Fairy", 
	"Blue Fire", "Glass", "Laser", "Crystal", "Air", "Black Hole",
	"Oil", "Urchin", "Dragon", "Critter", "Nuclear Explosion", 
	"Uranium", "Neutron", "Lightning", "Plasma", "Electron", "StormPlasma",
	"Hurricane", "Powder", "Liquid Powder", "Mercury", "Potassium",
	"PExplosion", "Hydrogen", "HExplosion", "Penguin", "BurningOil",
	"Gold", "MoltenGold", "MoltenGlass", "AlgaeRed", "AlgaeBrown", "CoolLava",
	"Obsidian", "Vapor", "AcidWater", "OxidizedPotassium", 
	"BurningPotassium", "Rust", "PowderB", "PowderC", "Kuiper", "Sun",
	"FireworkB", "FireworkC", "FireworkTrail", "Salt", "SaltWater",
	"Fish", "FishRight", "Strange", "Meteor", "MeteorB", "MeteorC",
	"Lapis", "Ruby", "Emerald", "Worm Hole"]

var POWDER = {}
var FLUID = {}

@export var save_file_manager: Node
@export var canvas: TextureRect
var sim: SandSimulation

@export var simulation_speed: int = 3
@export var chunk_size: int = 8
@export var brush_size: int = 16

var selected_element: int = 1
var pause := false

var draw_enabled: bool = false:
	set(value):
		draw_enabled = value
		var connected: bool = canvas.mouse_pressed.is_connected(_on_mouse_pressed)
		if draw_enabled and not connected:
			canvas.mouse_pressed.connect(_on_mouse_pressed)
		elif connected:
			canvas.mouse_pressed.disconnect(_on_mouse_pressed)

func _ready() -> void:
	canvas.resized.connect(_on_window_resized)
	
	for i in [3, 5, 20, 21, 24, 28, 30, 37, 39, 41, 44, 47, 66]:
		FLUID[i] = true
	for i in [1, 11, 12, 16, 42, 4, 8, 23, 31, 32, 33, 49, 63, 64, 45, 70, 72, 75]:
		POWDER[i] = true
	
	sim = SandSimulation.new()
	sim.set_chunk_size(chunk_size)
	_on_window_resized()

func _on_window_resized() -> void:
	sim.resize(int(canvas.size.x / canvas.px_scale), int(canvas.size.y / canvas.px_scale))
	canvas.repaint(sim)

# Thanks to Saideep Dicholkar for this implementation of Bresenham's Line Algorithm
# https://saideepdicholkar.blogspot.com/2017/04/bresenhams-line-algorithm-thick-line.html
func _on_mouse_pressed(start: Vector2, end: Vector2) -> void:
	if start.distance_to(end) > brush_size / 2.0:
		if abs(end.y - start.y) / abs(end.x - start.x) < 1:
			var wy: float = brush_size * sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2)) / (2 * abs(end.x - start.x))
			if is_equal_approx(end.x, start.x):
				wy = 0
			var i: int = 0
			while i < wy:
				draw_line(start.x, start.y - i, end.x, end.y - i)
				draw_line(start.x, start.y + i, end.x, end.y + i)
				i += 1
		else:
			var wx: float = brush_size * sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2)) / (2 * abs(end.y - start.y))
			var i: int = 0
			if is_equal_approx(end.y, start.y):
				wx = 0
			while i < wx:
				draw_line(start.x - i, start.y, end.x - i, end.y)
				draw_line(start.x + i, start.y, end.x + i, end.y)
				i += 1
	draw_circle(end.x, end.y, brush_size / 2)

func _process(_delta) -> void:
	if draw_enabled:
		sim.step(simulation_speed)
		canvas.repaint(sim)

# Helper method of the Bresenham's Line Algorithm; does not work stand-alone from _on_mouse_pressed
func draw_line(x1: float, y1: float, x2: float, y2: float) -> void:
	var xi: float = 1 if x1 < x2 else -1
	var yi: float = 1 if y1 < y2 else -1
	var x: float = x1
	var y: float = y1
	var dx: float = abs(x2 - x1)
	var dy: float = abs(y2 - y1)
	draw_pixel(y, x)
	if dx >= dy:
		var e = 2 * dy - dx
		while (xi < 0 and x > x2) or (xi > 0 and x < x2):
			if e < 0:
				e += 2 * dy
			else:
				e += 2 * (dy - dx)
				y += yi
			x += xi
			draw_pixel(y, x)
	else:
		var e = 2 * dx - dy
		while (yi < 0 and y > y2) or (yi > 0 and y < y2):
			if e < 0:
				e += 2 * dx
			else:
				e += 2 * (dx - dy)
				x += xi
			y += yi
			draw_pixel(y, x)

func draw_circle(x: float, y: float, radius: float) -> void:
	if not sim.in_bounds(roundi(y), roundi(x)):
		return
	for row in range(-radius, radius + 1):
		for col in range(-radius, radius + 1):
			if row*row + col*col < radius*radius:
				draw_pixel(row + y, col + x)

func draw_pixel(row: float, col: float) -> void:
	if selected_element in POWDER and randf() > 0.1:
		return
	
	var y: int = roundi(row)
	var x: int = roundi(col)
	if not sim.in_bounds(y, x):
		return
	
	var at: int = sim.get_cell(y, x)
	
	# Do not allow fluids to be drawn over solids, unless its fire over vapor/smoke
	if selected_element in FLUID and not at == 0:
		if not ((selected_element == 5 or selected_element == 24) and (at == 6 or at == 58)):
			return 
	
	if selected_element in [42, 63, 64]:
		selected_element = [42, 63, 64][randi() % 3]
	
	if selected_element in [75, 76, 77]:
		selected_element = [75, 76, 77][randi() % 3]
	
	sim.draw_cell(y, x, selected_element)

func clear() -> void:
	for i in range(sim.get_height()):
		for j in range(sim.get_width()):
			sim.draw_cell(i, j, 0)
	canvas.repaint(sim)

func save_image(path: String) -> void:
	canvas.texture.get_image().save_png(path)

func load_image(path: String) -> void:
	clear()
	var img: Image = Image.load_from_file(path)
	for i in range(sim.get_height()):
		for j in range(sim.get_width()):
			if j >= img.get_width() or i >= img.get_height():
				continue
			sim.set_cell(i, j, int(255 * img.get_pixel(j, i).r))
	canvas.repaint(sim)

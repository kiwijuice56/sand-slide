extends Node
class_name ElementManager

# Manages custom elements, sending information to the simulation and saving resources

# SORRY I know this should be in its own text file but I don't want to bother
# with more file management on android than I have to
const RANDOM_ELEMENT_NAMES: Array[String] = ['likely', 'meant', 'end', 'its', 'early', 
'sort', 'fair', 'beat', 'copper', 'happen', 'ruler', 'grown', 'series', 'muscle', 
'coach', 'fly', 'time', 'safety', 'act', 'worry', 'hang', 'best', 'fresh', 'sick',
'nuts', 'forth', 'should', 'birth', 'swim', 'magic', 'alive', 'differ', 'about', 
'bottle', 'hot', 'lay', 'into', 'shore', 'main', 'push', 'rule', 'little', 'farmer', 
'vapor', 'sang', 'music', 'do', 'fill', 'tell', 'trail', 'bad', 'her', 'noise', 'flow', 
'tank', 'smile', 'flies', 'hello', 'rabbit', 'sheet', 'hurt', 'amount', 'spent', 'from', 
'lot', 'find', 'flight', 'desk', 'entire', 'tall', 'rough', 'mouth', 'herd', 'hand', 
'them', 'depth', 'nice', 'form', 'year', 'tongue', 'did', 'barn', 'port', 'sad',
'wonder', 'jungle', 'child', 'kind', 'well', 'anyway', 'wheel', 'edge', 'wagon', 
'two', 'meet', 'sport', 'first', 'smooth', 'is', 'doubt', 'shoe', 'dot', 'verb', 
'job', 'are', 'yes', 'finest', 'all', 'save', 'source', 'strong', 'tide', 'orange', 
'making', 'wealth', 'piece', 'get', 'partly', 'stay', 'high', 'salmon', 'wet', 'radio', 
'clear', 'fact', 'bite', 'shine', 'news', 'pond', 'bone', 'stop', 'wide', 'taste', 
'laid', 'shot', 'color', 'stage', 'wild', 'stand', 'slight', 'sudden', 'parent', 
'habit', 'out', 'forest', 'would', 'pole', 'topic', 'three', 'driver', 'orbit', 'gate', 
'coming', 'break', 'shoot', 'inside', 'glass', 'read', 'north', 'hollow', 'behind', 
'park', 'hung', 'fourth', 'saw', 'coffee', 'ask', 'guide', 'sets', 'fallen', 'riding', 
'dish', 'widely', 'air', 'learn', 'giving', 'twenty', 'game', 'these', 'burst', 
'expect', 'tool', 'car', 'cream', 'serve', 'knew', 'bottom', 'rubber', 'call', 'result', 
'season', 'up', 'waste', 'steel', 'system', 'pay', 'period', 'plan', 'ever', 'curve', 
'were', 'direct', 'red', 'go', 'select', 'trap', 'hall', 'mail', 'create', 'either', 
'next', 'garden', 'forget', 'lamp', 'top', 'ship', 'bush', 'pipe', 'to', 'melted', 
'bread', 'swept', 'fewer', 'sheep', 'zero', 'fish', 'plus', 'paint', 'sense', 'begun', 
'done', 'angry', 'nodded', 'finish', 'night', 'buy', 'anyone', 'rate', 'water', 'while', 
'few', 'camp', 'turn', 'please', 'truth', 'thrown', 'shelf', 'race', 'stairs', 'avoid', 
'prove', 'doctor', 'longer', 'strike', 'nose', 'later', 'battle', 'paper', 'until', 
'hay', 'lead', 'accept', 'sun', 'soon', 'cast', 'family', 'rice', 'quite', 'eaten', 
'sleep', 'planet', 'border', 'wall', 'very', 'bill', 'third', 'slowly', 'hidden', 
'labor', 'hit', 'scared', 'court', 'bet', 'does', 'carbon', 'brass', 'see', 'birds', 
'pure', 'rhyme', 'low', 'band', 'nation', 'using', 'met', 'store', 'weight', 'table', 
'mill', 'indeed', 'able', 'spell', 'struck', 'attack', 'nor', 'grain', 'thirty', 'dig', 
'suit', 'spite', 'aware', 'dozen', 'speak', 'poor', 'gave', 'food', 'gun', 'wheat', 
'proper', 'press', 'reach', 'dollar', 'taught', 'kept', 'five', 'right', 'mirror', 
'went', 'dance', 'worker', 'value', 'yet', 'exact', 'found', 'vast', 'space', 'ill', 
'day', 'plane', 'globe', 'review', 'graph', 'size', 'art', 'loud', 'across', 'boat', 
'tone', 'of', 'both', 'frozen', 'stove', 'wear', 'rod', 'course', 'advice', 'say',
'clay', 'corn', 'saddle', 'you', 'meal', 'else', 'answer', 'stood', 'our', 'law', 
'pony', 'old', 'nobody', 'piano', 'number', 'shadow', 'than', 'cheese', 'bigger', 
'breath', 'it', 'thread', 'leaf', 'west', 'oldest', 'calm', 'ants', 'bee', 'lower', 
'skin', 'one', 'will', 'load', 'simple', 'army', 'plate', 'person', 'mark', 'they', 
'spirit', 'prize', 'spider', 'final', 'been', 'knife', 'stiff', 'pretty', 'noun', 
'be', 'boy', 'dead', 'has', 'damage', 'storm', 'shirt', 'throat', 'church', 'route', 
'dried', 'driven', 'drink', 'as', 'mighty', 'take', 'notice', 'dug', 'sea', 'daily', 
'column', 'coat', 'new', 'guard', 'tip', 'sugar', 'lion', 'buried', 'lost', 'brick', 
'took', 'silent', 'still', 'taken', 'golden', 'inch', 'field', 'needle', 'eye', 'canal', 
'flew', 'length', 'eager', 'roar', 'forgot', 'ranch', 'figure', 'fix', 'dog', 'height', 
'pick', 'heat', 'leg', 'fear', 'powder', 'over', 'settle', 'human', 'today', 'black', 
'wave', 'small', 'moment', 'seems', 'myself', 'send', 'flower', 'also', 'pilot', 'crew',
'uncle', 'egg', 'poetry', 'pain', 'tired', 'fought', 'lack', 'modern', 'sight', 'tail', 
'said', 'stuck', 'metal', 'matter', 'aboard', 'cell', 'oxygen', 'thick', 'fog', 'come', 
'voice', 'yellow', 'sent', 'hair', 'maybe', 'tears', 'least', 'watch', 'soil', 'girl', 
'lovely', 'refer', 'cattle', 'silver', 'sink', 'upper', 'far', 'deer', 'larger', 'idea', 
'nails', 'hat', 'bent', 'born', 'union', 'square', 'fierce', 'drawn', 'what', 'search', 
'won', 'empty', 'spoken', 'bound', 'around', 'sell', 'draw', 'class', 'slept', 'sum', 
'trade', 'front', 'guess', 'soap', 'thus', 'camera', 'closer', 'growth', 'weigh', 'roll', 
'fell', 'needed', 'scene', 'dress', 'world', 'seed', 'though', 'by', 'string', 'tales', 
'men', 'strip', 'skill', 'charge', 'dinner', 'eat', 'count', 'gone', 'burn', 'kids', 
'area', 'broken', 'star', 'speech', 'iron', 'circle', 'thumb', 'most', 'grew', 'might', 
'upon', 'seldom', 'grass', 'saved', 'hungry', 'depend', 'center', 'lose', 'book', 
'former', 'branch', 'bus', 'duck']

var element_materials: Array[Element]
var element_map: Dictionary
var custom_element_map: Dictionary

func _ready() -> void:
	Settings.background_updated.connect(set_background_color)
	
	element_materials = []
	var dir: DirAccess = DirAccess.open("res://main/element_manager/element_material")
	for file in dir.get_files():
		# Android devices store resource filenames with the .remap extension.
		# As long as the code provides a valid path, Godot will find the linked resource.
		file = file.replace(".remap", "")
		element_materials.append(ResourceLoader.load("%s/%s" % [dir.get_current_dir(), file]))
	for mat in element_materials:
		element_map[mat.id] = mat
	
	# Load custom element data
	custom_element_map = {}
	dir = DirAccess.open("user://")
	for file in dir.get_files():
		if not file.ends_with(".tres"):
			continue
		if file == "config.tres":
			continue
		var custom_element: CustomElement = ResourceLoader.load("user://" + file)
		custom_element_map[custom_element.id] = custom_element
	
	await get_tree().get_root().ready
	
	initialize_custom_elements()
	set_background_color(Settings.bg_color)

func create_new_element() -> void:
	var id: int = 2048
	while id in custom_element_map:
		id += 1
	if id > 4096:
		print("too many elements!!")
		return
	var new_element: CustomElement = CustomElement.new()
	new_element.id = id
	new_element.display_name = RANDOM_ELEMENT_NAMES.pick_random()
	new_element.color_a = Color.from_hsv(randf(), randf(), randf())
	if randf() < 0.5:
		new_element.style = 0
		new_element.color_b = new_element.color_a
		new_element.color_c = new_element.color_a
	else:
		new_element.style = 1
		new_element.color_b = Color.from_hsv(randf(), randf(), randf())
		new_element.color_c = Color.from_hsv(randf(), randf(), randf())
	new_element.state = randi() % 4
	new_element.density = randf()
	new_element.viscosity = randf()
	new_element.conductivity = randf()
	new_element.temperature = randf()
	new_element.flammability = randf()
	new_element.reactivity = randf()
	new_element.durability = randf()
	new_element.power = randf()
	new_element.explosive = randf() < 0.3
	new_element.alive = randf() < 0.3
	new_element.toxic = randf() < 0.3
	new_element.evaporable = randf() < 0.3
	
	custom_element_map[id] = new_element
	Settings.custom_element_ordering.append(id)
	Settings.save_settings()
	initialize_custom_elements()
	save_elements()

func save_elements() -> void:
	for element in custom_element_map.values():
		ResourceSaver.save(element, "user://" + str(element.id) + element.display_name + ".tres")

func initialize_custom_elements() -> void:
	var pass_dict: Dictionary = {}
	for element in custom_element_map.values():
		var custom_element: CustomElement = element
		pass_dict[custom_element.id] = []
		pass_dict[custom_element.id].append(custom_element.state)
		pass_dict[custom_element.id].append(custom_element.density)
		pass_dict[custom_element.id].append(custom_element.viscosity)
		pass_dict[custom_element.id].append(custom_element.conductivity)
		pass_dict[custom_element.id].append(custom_element.temperature)
		pass_dict[custom_element.id].append(custom_element.flammability)
		pass_dict[custom_element.id].append(custom_element.reactivity)
		pass_dict[custom_element.id].append(custom_element.durability)
		pass_dict[custom_element.id].append(custom_element.power)
		pass_dict[custom_element.id].append(custom_element.explosive)
		pass_dict[custom_element.id].append(custom_element.evaporable)
		pass_dict[custom_element.id].append(custom_element.alive)
		pass_dict[custom_element.id].append(custom_element.toxic)
		
	CommonReference.main.sim.initialize_custom_elements(pass_dict)
	initialize_element_graphics()

func initialize_element_graphics() -> void:
	var flat_color: Dictionary = {}
	for mat in element_materials:
		if not mat is FlatColor:
			continue
		flat_color[mat.id] = mat.color.to_rgba32()
	CommonReference.main.sim.initialize_flat_color(flat_color)
	var gradient_color: Dictionary = {}
	for mat in element_materials:
		if not mat is GradientColor:
			continue
		gradient_color[mat.id] = [
			mat.color_a.to_rgba32(),
			mat.color_b.to_rgba32(),
			mat.color_c.to_rgba32(),
			mat.color_d.to_rgba32(),
			mat.color_e.to_rgba32(),
			mat.offset_1,
			mat.offset_2,
			mat.offset_3
		]
	CommonReference.main.sim.initialize_gradient_color(gradient_color)
	
	var fluid_color: Dictionary = {}
	for mat in element_materials:
		if not mat is Fluid:
			continue
		fluid_color[mat.id] = [
			mat.color_a.to_rgba32(),
			mat.color_b.to_rgba32(),
			mat.color_c.to_rgba32(),
		]
	for element in custom_element_map.values():
		fluid_color[element.id] = [
			element.color_a.to_rgba32(),
			element.color_b.to_rgba32(),
			element.color_c.to_rgba32(),
		]
	CommonReference.main.sim.initialize_fluid_color(fluid_color)
	var metal_color: Dictionary = {}
	for mat in element_materials:
		if not mat is Metal:
			continue
		metal_color[mat.id] = [
			mat.color_a.to_rgba32(),
			mat.color_b.to_rgba32(),
		]
	CommonReference.main.sim.initialize_metal_color(metal_color)

func set_background_color(color: Color) -> void:
	element_map[0].color = color
	initialize_element_graphics()
	CommonReference.canvas.repaint()

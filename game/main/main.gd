extends Node
class_name Main

# Initializes the SandSimulation object and acts as an interface for other nodes to 
# interact with said object. Also runs the main processing of the simulation.

var sim: SandSimulation

var active: bool = false

func _ready() -> void:
	sim = SandSimulation.new()
	# I haven't benchmarked extensively yet, but this chunk size has reasonable 
	# performance.
	sim.set_chunk_size(16)
	
	await get_tree().get_root().ready
	CommonReference.canvas.resized.connect(_on_window_resized)
	
	# This method would not be called without signals normally, but the window size
	# must be initialized at the start of the game.
	_on_window_resized()

func _on_window_resized() -> void:
	sim.resize(int(CommonReference.canvas.size.x / Settings.px_scale), int(CommonReference.canvas.size.y / Settings.px_scale))
	CommonReference.canvas.repaint()

func _process(_delta: float) -> void:
	if active:
		sim.step(Settings.simulation_speed)
		CommonReference.canvas.repaint()

extends MarginContainer

func _ready() -> void:
	$Timer.timeout.connect(_on_timeout)

func show_element(elem_name: String, description: String, color: Color):
	%ElementColor.modulate = color
	%ElementName.text = elem_name
	%ElementInfo.text = description
	$AnimationPlayer.stop()
	$AnimationPlayer.play("show")
	$Timer.start(5)

func _on_timeout():
	$AnimationPlayer.play("hide")

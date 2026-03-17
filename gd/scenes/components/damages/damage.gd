extends Node

signal dealt_damage

#signal give_damage(value: int)
@export var value: int = 1:
	get:
		dealt_damage.emit()
		return value


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

#func damage_health(parent: Node) -> void:
#
#	var hp := parent.find_child("Health")
#
#	if (hp != null):
#
#		give_damage.connect(hp.take_damage)
#

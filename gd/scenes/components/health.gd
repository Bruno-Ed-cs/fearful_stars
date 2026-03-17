extends Node

@export var total: int = 1
@export var value: int = 1:
	get:
		return value


# Called when the node enters the scene tree for the first time.
func _ready() -> void:

	value = total

	pass # Replace with function body.

#func _init(max_hp: int) -> void:
#
#	total = max_hp
#	value = max_hp


# Called every frme. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	if (value < 0):
		value = 0


	pass

func take_damage(damage: int) -> void:

	if (damage < 0):
		damage = 0

	value -= damage

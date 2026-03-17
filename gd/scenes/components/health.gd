extends Node

@export var invis_timer: Timer

@export var single_damage: bool = false
@export var total: int = 1
var value: int = 1:
	get:
		return value

signal death

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

	if (value <= 0):
		death.emit()

func take_damage(damage: int) -> void:

	if (damage < 0):
		damage = 0
	elif  (single_damage):
		damage = 1

	if (invis_timer != null):
		if (invis_timer.is_stopped()):
			invis_timer.start()
			value -= damage
			return
		else:
			return

	value -= damage

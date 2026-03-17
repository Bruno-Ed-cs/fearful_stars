extends Node

var colliding: bool = false
var collider: Area2D

@export var damage_groups: Array[String]

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:

	pass


func validate_collision(area: Area2D) -> bool:
	#print(area.get_parent().get_groups())

	var valid = true
	var parent_groups := area.get_parent().get_groups()

	for group in parent_groups:
		if (group not in damage_groups):
			valid = false




	if (valid):
		return true

	#print("valid")
	return false

func _on_area_exited(area: Area2D) -> void:

	if (validate_collision(area)):
		colliding = false


func _on_area_entered(area: Area2D) -> void:

	if (validate_collision(area)):
		collider = area
		colliding = true

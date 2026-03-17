extends Node2D

@export var speed: float = 50
@export var damage: int = 1
@export var direction := Vector2(1, 0)


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:

	var movement: Vector2 = (speed * direction) * delta
	movement.normalized()

	position += movement
	pass


func _on_area_2d_area_entered(area: Area2D) -> void:

	var groups := area.get_parent().get_groups()
	#print(groups)
	if ("Entity" in groups and not "Player" in groups):
		var health := area.get_parent().get_node("Health")

		if (area.get_parent().has_node("Health")):

			#print("that hurts")
			health.take_damage(damage)
		else:
			print("Does not exist")
			#print(area.get_parent().get_children())


	pass # Replace with function body.

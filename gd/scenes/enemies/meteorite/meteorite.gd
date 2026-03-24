extends Node2D

@export var speed: float = 15
@export var direction := Vector2(-1, 0)

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:

	var movement: Vector2 = (speed * direction) * delta

	movement.normalized()

	position += movement

	#print($Health.value)


	pass


func _on_collision(collider: Area2D) -> void:

	var damage_taken: Node = collider.find_child("Damage")
	if (damage_taken != null):
		$Health.take_damage(damage_taken.value)

func _on_death() -> void:

	queue_free()

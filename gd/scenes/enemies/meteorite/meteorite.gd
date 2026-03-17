extends Node2D

@export var speed: float = 15
@export var direction := Vector2(-1, 0)

@onready var hitbox := $Area2D/PersistentCollision

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:

	var movement: Vector2 = (speed * direction) * delta

	movement.normalized()

	position += movement

	#print($Health.value)

	if (hitbox.colliding):
		var damage_taken: Node = hitbox.collider.find_child("Damage")
		if (damage_taken != null):
			$Health.take_damage(damage_taken.value)

	pass


func _on_collision(area: Area2D) -> void:

#	damage.damage_health(area.get_parent())
#	damage.give_damage.emit(10)

	pass # Replace with function body.

func _on_death() -> void:

	queue_free()

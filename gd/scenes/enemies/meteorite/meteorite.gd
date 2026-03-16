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
	pass

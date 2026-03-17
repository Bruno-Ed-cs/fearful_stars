extends Node2D

@export var speed: float = 145.0
@onready var hp := $Health

var in_collision: bool = false
@onready var timer: Timer = $Timer

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	var direction: Vector2 = Input.get_vector("move_left", "move_right", "move_up", "move_down")
	var movement: Vector2 = (direction * speed) * delta

	movement.normalized()

	position += movement

	if (in_collision and timer.is_stopped()):
		timer.start()
		hp.take_damage(1)

	pass

func validate_collision(area: Area2D) -> bool:
	#print(area.get_parent().get_groups())
	if (area.get_parent().is_in_group("Player")):
		return false

	#print("valid")
	return true

func _on_area_2d_area_entered(area: Area2D) -> void:

	if (validate_collision(area)):
		in_collision = true

func _on_area_2d_area_exited(area: Area2D) -> void:

	if (validate_collision(area)):
		in_collision = false

func _on_timer_timeout() -> void:
	pass # Replace with function body.

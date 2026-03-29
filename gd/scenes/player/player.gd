extends CharacterBody2D

@export var speed: float = 100
@onready var hp := $Health

#@onready var timer: Timer = $Timer

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	var direction: Vector2 = Input.get_vector("move_left", "move_right", "move_up", "move_down")

	if (Input.is_action_pressed("slow_down")):

		velocity = direction * (speed * 0.70)
	else :
		velocity = direction * speed 


	#print(velocity)

	move_and_slide()

func _on_collision(collider: Area2D) -> void:
	#print("collided")
	var damage: Node = collider.owner.find_child("Damage")
	if (damage != null):
		hp.take_damage(damage.value)

func _on_death() -> void:
	print("you died")
	get_tree().reload_current_scene()


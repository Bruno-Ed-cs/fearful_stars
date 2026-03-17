extends Weapon

var projectile := preload("res://scenes/projectiles/plasma_shot.tscn")
@onready var main_scene := $/root/Main
@onready var timer: Timer = $Timer

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.

func shoot() -> void:

	if (timer.is_stopped()):
		timer.start()

		var instance := projectile.instantiate()
		instance.position = main_scene.get_node("Player").position
		main_scene.add_child(instance)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

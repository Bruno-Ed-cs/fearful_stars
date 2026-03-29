extends Area2D

var colliding: bool = false
var collider: Area2D

signal collision(collider: Area2D)

#@export var damage_groups: Array[String]

# Called when the node enters the scene tree for the first time.
func _ready() -> void:

	var parent := get_parent()
	var signals := parent.get_signal_list()

	var can_enter: bool = false
	var can_exit: bool = false

	for sig in signals:
		if (sig["name"] == "area_entered"): can_enter = true
		if (sig["name"] == "area_exited"): can_exit = true

		if (can_enter and can_exit): break

	if (can_enter and can_exit):
		#print("true")
		parent.area_entered.connect(_on_area_entered)
		parent.area_exited.connect(_on_area_exited)
	return


func _process(delta: float) -> void:

	if (colliding):
		#print(owner.name)
		collision.emit(collider)
		#print("colliding with " + collider.name)

	pass


# not in use right now because collision layers are just better
# func validate_collision(area: Area2D) -> bool:
# 
# 	#print(area.get_parent().get_groups())
# 
# 	var valid = true
# 	var parent_groups := area.get_parent().get_groups()
# 
# 	for group in parent_groups:
# 		if (group not in damage_groups):
# 			valid = false
# 
# 	if (valid):
# 		return true
# 
# 	#print("valid")
# 	return false

func _on_area_exited(area: Area2D) -> void:

	colliding = false


func _on_area_entered(area: Area2D) -> void:

	collider = area
	colliding = true

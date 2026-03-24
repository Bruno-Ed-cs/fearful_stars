extends Control

@onready var label_p := $LabelPlayer
@onready var label_m := $LabelMeteor
@onready var player_hp := $/root/Main/Player/Health
@onready var meteor_hp := $/root/Main/Meteorite/Health



# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:


	if (player_hp != null):
		label_p.text = "x " + str(player_hp.value)

	if (meteor_hp != null):
		label_m.text = "m = " + str(meteor_hp.value)

	pass

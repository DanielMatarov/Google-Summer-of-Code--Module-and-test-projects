extends AudioStreamPlayer

# class member variables go here, for example:
# var a = 2
# var b = "textvar"
var note = 53

func _ready():
	stream.set_filename("florestan-subset.sf2")
	stream.set_preset(0)
	for i in range(stream.get_preset_count()):
		$OptionButton.add_item(stream.get_preset_name(i))
	
	pass

func _input(event):
	if event.is_class("InputEventMIDI"):
			stream.note_on(event.get_pitch(), event.get_velocity()/127.0)
	pass

func _input2(event):
	if event.is_class("InputEventMIDI"):
		if event == 8:
			stream.note_off(event.get_pitch())
	pass

func _on_OptionButton_item_selected(p):
	stream.set_preset(p)
	pass # replace with function body


func _on_SpinBox_value_changed(volume):
	stream.set_channel_volume(0, volume)
	pass # replace with function body
	
func _on_SpinBox2Pan_value_changed(pan):
	stream.set_channel_pan(0, pan)
	pass # replace with function body

func _on_SpinBoxTuning_value_changed(tuning):
	stream.set_channel_tuning(0, tuning)
	pass # replace with function body
	

func _on_Area2DKey1_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note, 1.0)
			play(0.0)
		else:
			stream.note_off(note)
	pass 
	
func _on_Area2DKey1_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note,1.0)
	pass # replace with function body

func _on_Area2DKey1_mouse_exited():
	stream.note_off(note)
	pass # replace with function body



func _on_Area2DKey2_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+1, 1.0)
			play(0.0)
		else:
			stream.note_off(note+1)
	pass # replace with function body
	
func _on_Area2DKey2_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+1,1.0)
	pass # replace with function body

func _on_Area2DKey2_mouse_exited():
	stream.note_off(note+1)
	pass # replace with function body



func _on_Area2DKey3_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+2, 1.0)
			play(0.0)
		else:
			stream.note_off(note+2)
	pass # replace with function body
	
func _on_Area2DKey3_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+2,1.0)
	pass # replace with function body

func _on_Area2DKey3_mouse_exited():
	stream.note_off(note+2)
	pass # replace with function body



func _on_Area2DKey4_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+3, 1.0)
			play(0.0)
		else:
			stream.note_off(note+3)
	pass # replace with function body

func _on_Area2DKey4_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+3,1.0)
	pass # replace with function body

func _on_Area2DKey4_mouse_exited():
	stream.note_off(note+3)
	pass # replace with function body



func _on_Area2DKey5_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+4, 1.0)
			play(0.0)
		else:
			stream.note_off(note+4)
	pass # replace with function body

func _on_Area2DKey5_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+4,1.0)
	pass # replace with function body

func _on_Area2DKey5_mouse_exited():
	stream.note_off(note+4)
	pass # replace with function body



func _on_Area2DKey6_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+5, 1.0)
			play(0.0)
		else:
			stream.note_off(note+5)
	pass # replace with function body
	
func _on_Area2DKey6_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+5,1.0)
	pass # replace with function body

func _on_Area2DKey6_mouse_exited():
	stream.note_off(note+5)
	pass # replace with function body



func _on_Area2DKey7_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+6, 1.0)
			play(0.0)
		else:
			stream.note_off(note+6)
	pass # replace with function body
	
func _on_Area2DKey7_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+6,1.0)
	pass # replace with function body

func _on_Area2DKey7_mouse_exited():
	stream.note_off(note+6)
	pass # replace with function body



func _on_Area2DKey8_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+7, 1.0)
			play(0.0)
		else:
			stream.note_off(note+7)
	pass # replace with function body
	
func _on_Area2DKey8_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+7,1.0)
	pass # replace with function body

func _on_Area2DKey8_mouse_exited():
	stream.note_off(note+7)
	pass # replace with function body



func _on_Area2DKey9_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+8, 1.0)
			play(0.0)
		else:
			stream.note_off(note+8)
	pass # replace with function body

func _on_Area2DKey9_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+8,1.0)
	pass # replace with function body

func _on_Area2DKey9_mouse_exited():
	stream.note_off(note+8)
	pass # replace with function body



func _on_Area2DKey10_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+9, 1.0)
			play(0.0)
		else:
			stream.note_off(note+9)
	pass # replace with function body
	
func _on_Area2DKey10_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+9,1.0)
	pass # replace with function body

func _on_Area2DKey10_mouse_exited():
	stream.note_off(note+9)
	pass # replace with function body
	
	

func _on_Area2DKey11_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+10, 1.0)
			play(0.0)
		else:
			stream.note_off(note+10)
	pass # replace with function body
	
func _on_Area2DKey11_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+10,1.0)
	pass # replace with function body

func _on_Area2DKey11_mouse_exited():
	stream.note_off(note+10)
	pass # replace with function body



func _on_Area2DKey12_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+11, 1.0)
			play(0.0)
		else:
			stream.note_off(note+11)
	pass # replace with function body
	
func _on_Area2DKey12_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+11,1.0)
	pass # replace with function body

func _on_Area2DKey12_mouse_exited():
	stream.note_off(note+11)
	pass # replace with function body



func _on_Area2DKey13_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+12, 1.0)
			play(0.0)
		else:
			stream.note_off(note+12)
	pass # replace with function body
	
func _on_Area2DKey13_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+12,1.0)
	pass # replace with function body

func _on_Area2DKey13_mouse_exited():
	stream.note_off(note+12)
	pass # replace with function body



func _on_Area2DKey14_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+13, 1.0)
			play(0.0)
		else:
			stream.note_off(note+13)
	pass # replace with function body

func _on_Area2DKey14_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+13,1.0)
	pass # replace with function body

func _on_Area2DKey14_mouse_exited():
	stream.note_off(note+13)
	pass # replace with function body



func _on_Area2DKey15_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+14, 1.0)
			play(0.0)
		else:
			stream.note_off(note+14)
	pass # replace with function body

func _on_Area2DKey15_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+14,1.0)
	pass # replace with function body

func _on_Area2DKey15_mouse_exited():
	stream.note_off(note+14)
	pass # replace with function body



func _on_Area2DKey16_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+15, 1.0)
			play(0.0)
		else:
			stream.note_off(note+15)
	pass # replace with function body
	
func _on_Area2DKey16_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+15,1.0)
	pass # replace with function body

func _on_Area2DKey16_mouse_exited():
	stream.note_off(note+15)
	pass # replace with function body



func _on_Area2DKey17_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+16, 1.0)
			play(0.0)
		else:
			stream.note_off(note+16)
	pass # replace with function body

func _on_Area2DKey17_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+16,1.0)
	pass # replace with function body

func _on_Area2DKey17_mouse_exited():
	stream.note_off(note+16)
	pass # replace with function body



func _on_Area2DKey18_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+17, 1.0)
			play(0.0)
		else:
			stream.note_off(note+17)
	pass # replace with function body

func _on_Area2DKey18_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+17,1.0)
	pass # replace with function body

func _on_Area2DKey18_mouse_exited():
	stream.note_off(note+17)
	pass # replace with function body



func _on_Area2DKey19_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+18, 1.0)
			play(0.0)
		else:
			stream.note_off(note+18)
	pass # replace with function body
	
func _on_Area2DKey19_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+18,1.0)
	pass # replace with function body

func _on_Area2DKey19_mouse_exited():
	stream.note_off(note+18)
	pass # replace with function body



func _on_Area2DKey20_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+19, 1.0)
			play(0.0)
		else:
			stream.note_off(note+19)
	pass # replace with function body

func _on_Area2DKey20_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+19,1.0)
	pass # replace with function body

func _on_Area2DKey20_mouse_exited():
	stream.note_off(note+19)
	pass # replace with function body



func _on_Area2DKey21_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+20, 1.0)
			play(0.0)
		else:
			stream.note_off(note+20)
	pass # replace with function body

func _on_Area2DKey21_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+20,1.0)
	pass # replace with function body

func _on_Area2DKey21_mouse_exited():
	stream.note_off(note+20)
	pass # replace with function body



func _on_Area2DKey22_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+21, 1.0)
			play(0.0)
		else:
			stream.note_off(note+21)
	pass # replace with function body
	
func _on_Area2DKey22_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+21,1.0)
	pass # replace with function body

func _on_Area2DKey22_mouse_exited():
	stream.note_off(note+21)
	pass # replace with function body



func _on_Area2DKey23_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+22, 1.0)
			play(0.0)
		else:
			stream.note_off(note+22)
	pass # replace with function body

func _on_Area2DKey23_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+22,1.0)
	pass # replace with function body

func _on_Area2DKey23_mouse_exited():
	stream.note_off(note+22)
	pass # replace with function body



func _on_Area2DKey24_input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton:
		if event.is_pressed():
			stream.note_on(note+23, 1.0)
			play(0.0)
		else:
			stream.note_off(note+23)
	pass # replace with function body

func _on_Area2DKey24_mouse_entered():
	if Input.is_mouse_button_pressed(BUTTON_LEFT):
		stream.note_on(note+23,1.0)
	pass # replace with function body

func _on_Area2DKey24_mouse_exited():
	stream.note_off(note+23)
	pass # replace with function body


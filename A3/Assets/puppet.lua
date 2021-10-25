-- a3mark.lua
-- A very simple scene creating a trivial hierarchical puppet.
-- We'll use this scene as part of testing your assignment.
-- See a3mark.png for an example of what this file produces.

rootnode = gr.node('root')

red = gr.material({1.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 10)
blue = gr.material({0.0, 0.0, 1.0}, {0.1, 0.1, 0.1}, 10)
tan = 	gr.material({1.0, 0.9, 0.9}, {0.1, 0.1, 0.1}, 10)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
black = gr.material({0.2, 0.2, 0.2}, {0.1, 0.1, 0.1}, 10)

torso = gr.mesh('sphere','torso')
rootnode:add_child(torso)
torso:translate(0.0, 0.0, 0.0)
torso:scale(0.7, 1.5, 1.0)
torso:set_material(black)

shoulders = gr.mesh('sphere','shoulders')
torso:add_child(shoulders)
shoulders:translate(0.0, 1.25, 0.0)
shoulders:scale(0.8, 0.2, 0.2)
shoulders:set_material(black)

upper_left_arm = gr.mesh('sphere','upper_left_arm')
shoulders:add_child(upper_left_arm)
upper_left_arm:rotate('z', 80.0)
upper_left_arm:translate(-0.85, -0.55, 0.0)
upper_left_arm:scale(0.5, 0.08, 0.08)
upper_left_arm:set_material(black)

lower_left_arm = gr.mesh('sphere','lower_left_arm')
upper_left_arm:add_child(lower_left_arm)
lower_left_arm:rotate('z', -10.0)
lower_left_arm:translate(-0.85, 0.08, 0.0)
lower_left_arm:scale(0.4, 0.08, 0.08)
lower_left_arm:set_material(black)

left_hand = gr.mesh('sphere','left_hand')
lower_left_arm:add_child(left_hand)
left_hand:translate(-0.25, 0.0, 0.0)
left_hand:scale(0.2, 0.2, 0.2)
left_hand:set_material(white)

upper_right_arm = gr.mesh('sphere','upper_right_arm')
shoulders:add_child(upper_right_arm)
upper_right_arm:rotate('z', -80.0)
upper_right_arm:translate(0.85, -0.55, 0.0)
upper_right_arm:scale(0.5, 0.08, 0.08)
upper_right_arm:set_material(black)

lower_right_arm = gr.mesh('sphere','lower_right_arm')
upper_right_arm:add_child(lower_right_arm)
lower_right_arm:rotate('z', 10.0)
lower_right_arm:translate(0.85, 0.08, 0.0)
lower_right_arm:scale(0.4, 0.08, 0.08)
lower_right_arm:set_material(black)

right_hand = gr.mesh('sphere','right_hand')
lower_right_arm:add_child(right_hand)
right_hand:translate(0.25, 0.0, 0.0)
right_hand:scale(0.2, 0.2, 0.2)
right_hand:set_material(white)

head = gr.mesh('sphere','head')
shoulders:add_child(head)
head:translate(0.0, 0.85, 0.0)
head:set_material(black)

face = gr.mesh('sphere','face')
head:add_child(face)
face:translate(0.0, -0.1, 0.3)
face:scale(0.9, 0.8, 1.0)
face:set_material(tan)

left_ear = gr.mesh('sphere','left_ear')
head:add_child(left_ear)
left_ear:translate(-1.0, 1.0, 0.0)
left_ear:scale(0.8, 0.8, 0.8)
left_ear:set_material(black)

right_ear = gr.mesh('sphere','right_ear')
head:add_child(right_ear)
right_ear:translate(1.0, 1.0, 0.0)
right_ear:scale(0.8, 0.8, 0.8)
right_ear:set_material(black)

rootnode:translate(0.0, 0.0, -10.0)

return rootnode

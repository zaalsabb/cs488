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

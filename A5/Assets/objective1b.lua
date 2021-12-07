mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

pole = gr.cylinder('pole', {-50,  -200, 410}, 300, 2)
scene_root:add_child(pole)
pole:set_material(mat2)

sign = gr.cylinder('pole', {0,  0, 0}, 2, 30)
scene_root:add_child(sign)
sign:set_material(mat1)
sign:rotate('x',90)
sign:rotate('y',215)
sign:rotate('z',180)
sign:translate(-50,75,415)
white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, '../Objectives/objective1b.png', 512, 512,
	  {-100, 150, 600}, {100, -200, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light},{}, {3,15,15}, 1)

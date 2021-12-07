mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

cone1 = gr.cone('cone1', {-100, -150, 100}, 50, 20)
scene_root:add_child(cone1)
cone1:set_material(mat1)

cone2 = gr.cone('cone2', {100, -150, 100}, 50, 20)
scene_root:add_child(cone2)
cone2:set_material(mat1)

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, '../Objectives/objective1a.png', 512, 512,
	  {-100, 150, 600}, {100, -200, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light},{}, {3,15,15}, 1)

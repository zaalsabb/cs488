mat3 = gr.material({1.0, 0.6, 0.1}, {0.4, 0.4, 0.4}, 30)


scene_root = gr.node('root')

spalling_bump = gr.bump("wall_depth.png")

wall = gr.quad( 'wall', 'quad.obj')
wall:set_material(mat3)
wall:scale(700, 500, 500)
wall:translate(0, 0, -500)
wall:set_bump(spalling_bump)
scene_root:add_child(wall)

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, '../Objectives/objective3b.png', 512, 512,
	  {-100, 150, 600}, {100, -200, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light},{}, {3,15,15}, 1)

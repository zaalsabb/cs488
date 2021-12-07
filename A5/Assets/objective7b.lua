mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

road_perlin = gr.perlin(0.01,4,1000,1000);

ground = gr.quad( 'ground', 'quad.obj')
ground:set_material(mat3)
ground:set_perlin(road_perlin);
ground:scale(800, 350, 500)
ground:rotate('x', -90)
ground:translate(0, -200, -100)
scene_root:add_child(ground)

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, '../Objectives/objective7b.png', 512, 512,
	  {-100, 150, 600}, {100, -200, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light},{}, {3,15,15}, 1)

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

road_perlin = gr.perlin(0.01,4,1000,1000);

ground = gr.quad( 'ground', 'quad.obj')
ground:set_material(mat3)
ground:scale(800, 350, 500)
ground:rotate('x', -90)
ground:translate(0, -200, -100)
scene_root:add_child(ground)

cone1 = gr.cone('cone1', {-100, -150, 100}, 50, 20)
scene_root:add_child(cone1)
cone1:set_material(mat2)

cylinder2 = gr.cylinder('cylinder2', {100, -200, 100}, 50, 20)
scene_root:add_child(cylinder2)
cylinder2:set_material(mat1)

white_arealight = gr.arealight({0, 400.0, -800.0}, {0.9, 0.9, 0.9}, {1, 0, 0},50,50)

gr.render(scene_root, '../Objectives/objective8b.png', 1024, 1024,
	  {-100, 50, 600}, {100, -200, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {},{white_arealight}, {3,15,15}, 1)

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

wall = gr.mesh( 'wall', 'car.obj')
wall:set_material(mat3)
wall:scale(500, 350, 500)
-- wall:rotate('y', 45)
-- wall:rotate('z', 45)
-- wall:rotate('x', 45)
wall:translate(0, 0, -500)
scene_root:add_child(wall)

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, 'test.png', 256, 256,
	  {0, 0, 800}, {0,0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light})

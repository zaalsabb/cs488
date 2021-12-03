-- A simple scene with five spheres

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

t = gr.texture("test2.png")

-- s1 = gr.cylinder('s1', {0, -200, 100}, 100, 100)
-- scene_root:add_child(s1)
-- s1:set_material(mat1)
-- -- s1:set_texture(t)

wall = gr.quad( 'wall', 'surface2.obj',10,10 )
wall:set_material(mat3)
wall:set_texture(t)
wall:scale(200, 200, 200)
-- wall:rotate('y', 45)
-- wall:rotate('z', 45)
-- wall:rotate('x', 45)
wall:translate(0, 0, 100)

scene_root:add_child(wall)

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
magenta_light = gr.light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})

gr.render(scene_root, 'scene.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light, magenta_light})

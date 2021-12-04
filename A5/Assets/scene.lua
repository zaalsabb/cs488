-- A simple scene with five spheres

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

t = gr.texture("wall_img.png")
b = gr.bump("wall_depth.png")

-- s1 = gr.cone('s1', {0, -200, 100}, 100, 100)
-- scene_root:add_child(s1)
-- s1:set_material(mat1)
-- s1:translate(0, 100, 100)
-- s1:set_texture(t)
-- s1:rotate('x', 45)

wall = gr.quad( 'wall', 'surface.obj')
wall:set_material(mat3)
wall:set_texture(t)
wall:set_bump(b)
wall:scale(500, 500, 500)
wall:rotate('y', 45)
-- wall:rotate('z', 45)
-- wall:rotate('x', 45)
wall:translate(0, 0, -100)
scene_root:add_child(wall)

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, 'scene.png', 512, 512,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light})
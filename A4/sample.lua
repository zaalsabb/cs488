-- A simple scene with five spheres

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)
grass = gr.material({0.1, 0.7, 0.1}, {0.0, 0.0, 0.0}, 0)

scene_root = gr.node('root')
scene_root:rotate('X', -60)
scene_root:translate(0, 150, -100)

-- the floor
plane = gr.mesh( 'plane', 'Assets/plane.obj' )
scene_root:add_child(plane)
plane:set_material(grass)
plane:scale(500, 700, 1600)
plane:rotate('X', 90)
plane:translate(0, 0, -800)

s1 = gr.nh_sphere('s1', {0, 0, -600}, 100)
scene_root:add_child(s1)
s1:set_material(mat1)

s2 = gr.nh_sphere('s2', {-100, 200, -600}, 100)
scene_root:add_child(s2)
s2:set_material(mat2)

s3 = gr.nh_sphere('s3', {100, 200, -600}, 100)
scene_root:add_child(s3)
s3:set_material(mat3)

s4 = gr.nh_sphere('s4', {-300, 400, -600}, 100)
scene_root:add_child(s4)
s4:set_material(mat1)

s6 = gr.nh_sphere('s6', {-100, 400, -600}, 100)
scene_root:add_child(s6)
s6:set_material(mat2)

s7 = gr.nh_sphere('s7', {100, 400, -600}, 100)
scene_root:add_child(s7)
s7:set_material(mat3)

s8 = gr.nh_sphere('s8', {300, 400, -600}, 100)
scene_root:add_child(s8)
s8:set_material(mat1)

l1 = gr.light({-300.0, 350.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, 'sample.png', 500, 500,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {l1})

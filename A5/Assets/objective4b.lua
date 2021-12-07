mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

wall_texture = gr.texture("wall_img.png")
cone_texture = gr.texture("traffic_cone.png")
road_texture = gr.texture("road.png")
sign_texture = gr.texture("sign.png")

spalling_bump = gr.bump("wall_depth.png")

road_perlin = gr.perlin(0.01,4,1000,1000);

cone1 = gr.cone('cone1', {-100, -150, 100}, 50, 20)
scene_root:add_child(cone1)
cone1:set_material(mat1)
cone1:set_texture(cone_texture)

cone2 = gr.cone('cone2', {100, -150, 100}, 50, 20)
scene_root:add_child(cone2)
cone2:set_material(mat1)
cone2:set_texture(cone_texture)

pole = gr.cylinder('pole', {-50,  -200, 410}, 300, 2)
scene_root:add_child(pole)
pole:set_material(mat2)

sign = gr.cylinder('pole', {0,  0, 0}, 2, 30)
scene_root:add_child(sign)
sign:set_material(mat1)
sign:set_texture(sign_texture)
sign:rotate('x',90)
sign:rotate('y',215)
sign:rotate('z',180)
sign:translate(-50,75,415)

wall = gr.quad( 'wall', 'quad.obj')
wall:set_material(mat3)
wall:set_texture(wall_texture)
wall:set_bump(spalling_bump)
wall:scale(700, 500, 500)
wall:translate(0, 0, -500)
scene_root:add_child(wall)

ground = gr.quad( 'ground', 'quad.obj')
ground:set_material(mat3)
ground:set_texture(road_texture)
ground:set_perlin(road_perlin);
ground:scale(800, 350, 500)
ground:rotate('x', -90)
ground:translate(0, -200, -100)
scene_root:add_child(ground)

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, '../Objectives/objective4b.png', 512, 512,
	  {-100, 150, 600}, {100, -200, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light},{}, {3,5,15}, 1)

# CS 688 - Project

---
By: Zaid Al-Sabbag

## Compilation
------------
The program compilation process is unchanged from previous assignments. Assuming that the A5/ folder is in the same directory as the shared/ folder, which are both in the /cs488 directory which contains all the bundled libraries.

```bash
cd A5
premake4 gmake
make
```

## How to run (Manual)
------------
This is a raytracing project, so the user must run the executable from within the Assets folder. There are 17 scenes total, each showcasing a different objective, with (e.g. 8a) or without (e.g. 8b) a specified feature. The file "**scene.lua**" shows the final rendered scene.

```bash
cd Assets
../A5 scene.lua
```
The screenshot of the final scene is saved in A5/ under the name "**screenshot.png**". For the objectives scenes, the screenshots are saved in the A5/Objectives folder for **objectives 1-8**.

## Objectives
All the objectives are implemented as commands in the .lua file.

1. **Custom primitives (cone, cylinder)**
These are implemented as the following lua commands. For the cone primitive, (x,y,z) is the position of the top of the cone. For the cylinder primitive, (x,y,z) is the position of the bottom of the cylinder. Height and radius are the same for both.
```
cone = gr.cone('cone', {x, y, z}, height, radius)
cylinder = gr.cylinder('cylinder', {x, y, z}, height, radius)
```
2. **Texture mapping**
The user must first create a texture from an image file. For example:
```
sign_texture = gr.texture("sign.png")
```
Then, the texture is attached to a **Quad**, **Cone**, or **Cylinder** node using the following command:
```
sign = gr.cylinder('pole', {0,  0, 0}, 2, 30)
sign:set_texture(sign_texture)
```

3. **Bump mapping**
The user can add bumps to a quad object using a depth map image. To initialize the Bump object:
```
spalling_bump = gr.bump("wall_depth.png")
```
Then assign the Bump object to a Quad object:
```
wall = gr.quad( 'wall', 'quad.obj')
wall:set_bump(spalling_bump)
```

4. **Lens system (depth of field)**
The depth of field is controlled using three parameters, Aperture constant (A), focal length (f), and screen position (s). These paremeters are specified in the gr.render command in the 12th row:
```
gr.render(scene_root, '../Objectives/objective4b.png', 512, 512,
	  {-100, 150, 600}, {100, -200, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light},{}, **{A,f,s}**, 1)
```

5. **Ray-Quad Intersection**
A quad mesh object was implemented as an extra feature in addition to triangular mesh. The Quad object is initialized as follows:
```
wall = gr.quad( 'wall', 'quad.obj')
```
The quad.obj file looks like this:
```
o quad

v -1 -1 0
v 1 -1 0
v 1 1 0
v -1 1 0

f 1 2 3 4
```

6. **Anti-aliasing**
In this project, anti-aliasing was implemented using super-resolution, then averaging of the pixels of each block. The user can set the scale (S) of the super-resolution in the gr.render command in the 13th row:
```
gr.render(scene_root, '../Objectives/objective6b.png', 512, 512,
	  {-100, 150, 600}, {100, -200, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light},{}, {3,15,15}, **S**)
```

7. **Perlin Noise**
Perlin noise was implemented using a pre-generated random seed number. The user first creates a perlin object by specifying the noise amplitude (a), octave (o), and resolution (w,h).
```
road_perlin = gr.perlin(a,o,w,h)
```
The generated random height is then treated as a bump map when performing normal calculations. 

8. **Soft shadows (area light)**
Soft shadows are implemented by sampling a light source inside a radius (R) multiple times, and the light source's position is randomly selected inside R. The user also specifies the number of samples (N).
```
arealight = gr.arealight({x,y,z}, {r,g,b}, {1, 0, 0}, **R**, **N**)
```
The user then adds the list of area light sources to the gr.render command in the 11th row:
```
gr.render(scene_root, '../Objectives/objective8b.png', 1024, 1024,
	  {-100, 50, 600}, {100, -200, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {**pointlight1,pointlight2,pointlight3**},{**arealight1,arealight2,arealight3**}, {3,15,15}, 1)
```

9. **Acceleration data structure for triangle/quad meshes (octree)**
Unfortunately this objective was not implemented due to limited time.

10. **Final scene (bridge structure with spalling, car, cones, and traffic sign)**
The final rendered scene can be found in **A5/screenshot.png**. The car was not included in this scene because none of the complex models I found online were compatible unfortunately.



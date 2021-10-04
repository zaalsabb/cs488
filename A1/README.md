# CS 688 - Assignment 1

---

## Compilation
------------
The program compilation process is unchanged from the instructions. Assuming that the A1/ folder is in the same directory as the shared/ folder, which are both in the /cs488 directory which contains all the bundled libraries.

```
cd A1
premake4 gmake
make
```

## Manual
------------
1. **Running the program**: The program should run using the command ./A1 and then it performs all the required functions in the objectives list.
2. **Maze start position**: When the maze is generated (either using UI button or pressing 'D'), then the avatar is placed at the top-most empty spot at the start of the maze.
3. **Rendering the cube**: I split it up into 12 triangles and I followed this [tutorial](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/). I modified the coordinates of the cube's vertices so that the total size of the cube is 1 x 1 x 1.
4. **Rendering the sphere**: I rendered 100 circular wireframes stacked on top of one another vertically and horizontally. When viewed at normal or even close distance, the lines appear as though they are a solid sphere. I used the equations from this [songho tutorial](http://www.songho.ca/opengl/gl_sphere.html) to get the coordinates of the vertices to render the lines.
5. **zoom-in and zoom-out**: I simply change the fov values of the camera perspective matrix.
6. **Rotation effect**: I apply a rotation to the model-to-world transformations of all objects in the scene.
7. **Change color values in the UI**: drag your mouse sideways on the slider.

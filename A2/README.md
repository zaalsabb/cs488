# CS 688 - Assignment 2

---

## Compilation
------------
The program compilation process is unchanged from the instructions. Assuming that the A2/ folder is in the same directory as the shared/ folder, which are both in the /cs488 directory which contains all the bundled libraries.

```
cd A2
premake4 gmake
make
```

## Manual/Notes
------------
1. **Running the program**: The program should run using the command ./A2 and then it performs all the required functions in the objectives list.
2. **Initial Viewport/Perpective parameters**: The viewport is initialized at location (0,0,-15). The initial clipping values are 1.0f and 50.0f.
3. **Model Transformations**: Model transformations are performed relative to the cube's local axis.
4. **Gnomes**: The cube's local axis and the world axis have different colors.
5. **Perspective**: I constructed the full perspective projection matrix.
6. **Near/Far Clipping Min Values**: I clip both the cube and gnomes. The near plane cannot be lower than 0.01, and the far plane cannot be lower than 0.02. Near/far clipping is performed before the projection transformation.
7. **Other**: All other features work as described in the Assignment 2 objectives list.

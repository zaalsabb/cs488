# CS 688 - Assignment 4

---

## Compilation
------------
The program compilation process is unchanged from the instructions. Assuming that the A4/ folder is in the same directory as the shared/ folder, which are both in the /cs488 directory which contains all the bundled libraries.

```bash
cd A4
premake4 gmake
make
```

## How to run
------------
For files inside Assets folder (simple.lua, hier.lua, nonhier.lua, etc.) do the following to run them from inside Assets folder:

```bash
cd Assets
../A4 nonhier.lua
```
The screenshot will be saved inside the Assets folder as well.

For files in A4/ folder that are outside Assets folder (sample.lua) do the following:

```bash
./A4 sample.lua
```
The screenshot will be saved in A4/ folder.

## Notes about Implemented Objectives
------------
1. Unfortunately, I was not able to implement hierarchical transformations fully correctly. My implementation of hierarchical transformations do work for hier.lua, but not for simple-cow.lua or macho-cow.lua. This is possibly because my code could not resolve the correct order for local scale, translation, and rotation of objects.
2. Other required features such as shadows, mesh/sphere/cube intersections all work correctly.
3. I implemented reflections and refractions as my additional feature for this assignment. These are controlled through the calculated Fresnel term.
4. My novel scene of a pool table is in sample.lua, which can be seen in sample.png. My best looking scene is in screenshot.png (nonhier scene).
5. To speed up computations, some parameters such as shadows, reflections, and recursion depth can be turned off or modified at the top of the A4.cpp file. Other parameters such as index of refraction for solids (default = 6) can also be changed.
6. **References:** The reflections/refractions algorithm was inspired from lecture notes in (1). The triangle intersection algorithm was implemented from (2). The progressbar file header file was imported directly from the repository in (3).

## References
------------
1. [CSE 681:Reflection and Refraction](https://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/reflection_refraction.pdf)
2. [Point in triangle test](https://blackpawn.com/texts/pointinpoly/)
3. [gipert/progressbar](https://github.com/gipert/progressbar)




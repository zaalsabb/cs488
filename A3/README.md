# CS 688 - Assignment 3

---

## Compilation
------------
The program compilation process is unchanged from the instructions. Assuming that the A3/ folder is in the same directory as the shared/ folder, which are both in the /cs488 directory which contains all the bundled libraries.

```
cd A2
premake4 gmake
make
```

## Notes
------------
Unfortunately, due some difficulties I was not able to implement controlling the joint angles. Therefore, many of the features are not implemented. Here's a full list of what was accomplished:

**Implemented**
1. Render a3mark.lua with correct transformations and lighting.
2. Create puppet.lua of mickey mouse character by specifying hierarchical transformations.
3. When clicking on a member, its color changes to red. Therefore, picking works correctly.
4. Z-buffer
5. Back/Front culling
6. Translate and rotate the entire puppet using the specified mouse controls (left, middle, and right clicks).
7. Reset puppet state.
8. Joint angles automatically move when the puppet is translated, demonstrating that the joints are not rigid.

**Not Implemented**
1. Cannot control joints angle. The angle for all joints changes by itself when translating the puppet and are not controlled by the mouse.

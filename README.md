# Triangle Rasterizer in C++ with the Windows 32-bit API

*Note: Only works on windows*

### What it does:

A triangle rasterizer is a program that takes three vertices in screen space and fills designated pixels in an outline to draw a triangle. If the three vertices are different colors, a process called interpolation interpolates (makes a gradient) out of the lines and you get the signature starter OpenGL/WebGL triangle with 1 red vertex, 1 blue and 1 green which is a great example of it.

## VERY IMPORTANT:

If you haven't seen at the top, this program will only work on windows or a machine that has the Windows API installed on it. This is because the Windows API holds all the functions to display pixel data on the heap and it handles all the window creation, destruction, resizing and more.

### Lessons/Concepts I learned and now understand

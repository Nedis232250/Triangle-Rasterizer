# Triangle Rasterizer in C++ with the Windows 32-bit API

*Note: Only works on windows*

### What it does:

A triangle rasterizer is a program that takes three vertices in screen space and fills designated pixels in an outline to draw a triangle. If the three vertices are different colors, a process called interpolation interpolates (makes a gradient) out of the lines and you get the signature starter OpenGL/WebGL triangle with 1 red vertex, 1 blue and 1 green which is a great example of it.

## VERY IMPORTANT:

If you haven't seen at the top, this program will only work on windows or a machine that has the Windows API installed on it. This is because the Windows API holds all the functions to display pixel data on the heap and it handles all the window creation, destruction, resizing and more.

### Lessons/Concepts I learned and now understand

#### 1. Templates:

Even though I didn't use templates in my project, earlier versions that didn't work out as expected did use templates and I understand their function clearly and I feel like my future projects will depend on them a lot. I feel like C++ templates are a programming concept that I am grateful to know how to use.

#### 2. Don't depend on excessive use of "std::vector" and manual heap allocation is a good tool when you know how to safely use it (the old adage, "with great power comes great responsibility"):

In earlier prototypes of this triangle rasterizer, I depended on heavy use of std::vector because I wasn't confident in my use of manual heap allocation (malloc()/realloc()) so I used excessive amounts of vectors and templates to include the types of the vectors in my first prototype which turned out to be a big mistake. The manual amount of allocation needed to run the rasterizer made it run at under 10 frames per second and froze my entire computer for about half a minute after I resized, opened or closed the window. This was probably because of the destruction and recreation of the vector that was storing pixel data and shifting the previous vector's data into a "holding vector" stupidly named "temp" which gave my computer a stroke. Lesson learned, use manual heap allocation (thankfully this project made me a lot more confident with it)

#### 3. Refrain from the use of the Windows API function: "COLORREF SetPixel([in] HDC hdc, [in] int x, [in] int y, [in] COLORREF color);" as I found it to be impossible to make it asynchronous with the <future> header and the whole screen filled up with pixels slowly. Like really slowly (this was done in VS community edition 2022 release x64):

It just didn't work, I figured it was way too slow for my liking. This project was not only meant to work, but it had to be fast enough to actually be used practically.

# Triangle Rasterizer in C++ with the Windows 32-bit API

*Note: Only works on Windows*

### What it does:

A triangle rasterizer is a program that takes three vertices in screen space and fills designated pixels in an outline to draw a triangle. If the three vertices are different colors, a process called interpolation makes a gradient out of the lines and you get a triangle with a gradient effect.

## VERY IMPORTANT:

This program will only work on Windows or a machine that has the Windows API installed on it. This is because the Windows API holds all the functions to display pixel data on the heap and it handles the window creation, destruction, resizing and many other Windows functions.

### How to use:

1: Open Visual Studio 2022 Community Edition and create a project.  
2: Delete all the code in the existing file.  
3: There should be a tab on the right side of the screen that says your project name. There are two of these, the one on the bottom is the correct one. Right click it, click properties, go to "Linker" then "System" and change the "SubSystem" parameter from "Console (/SUBSYSTEM:CONSOLE)" to "Windows (/SUBSYSTEM:WINDOWS)". Click apply then ok.  
4: Create the six C++/header files with the correct names and paste the code from the repository into the files.  
5: At the top of your screen, there is a button that says "Local Windows Debugger". There are some dropdowns that probably are set to "Debug" and "x64" keep the "x64" and change the "Debug" to "Release". Click the "Local Windows Debugger" to run the program (it will autosave when you run it).  

*YouTube video showing how to use this:*

### Lessons/Concepts I learned and now understand

#### 1. Templates:

Even though I didn't use templates in my project, earlier versions that didn't work out as expected did use templates and I understand their function clearly and I feel like my future projects will depend on them a lot. I feel like C++ templates are a programming concept that I am grateful to know how to use.

#### 2. Don't depend on excessive use of "std::vector" and manual heap allocation is a good tool when you know how to safely use it (the old adage, "with great power comes great responsibility"):

In earlier prototypes of this triangle rasterizer, I used excessive amounts of vectors and templates because I wasn't confident in my manual heap allocation skills (malloc()/realloc()). This turned out to be a big mistake. The amount of vector transferring, destruction and recreation needed to run the rasterizer made it run at under 10 frames per second and froze my entire computer for about half a minute after I resized, opened or closed the window. This was probably because of the destruction and recreation of the vector that was storing pixel data and shifting the previous vector's data into a "holding vector" stupidly named "temp" which gave my computer a stroke. Lesson learned. Use manual heap allocation (thankfully this project made me a lot more confident with it)

#### 3. Refrain from the use of the Windows API function: "COLORREF SetPixel([in] HDC hdc, [in] int x, [in] int y, [in] COLORREF color);" as I found it to be impossible to make it asynchronous with the <future> header and the whole screen filled up with pixels slowly. Like really slowly (this was done in VS community edition 2022 release x64):

It just didn't work. I figured it was way too slow for my liking. This project was not only meant to work, but it had to be fast enough to be used practically.

### Future improvements:

- I might want to create a vertex/fragment shader
- Optimize with NVidia CUDA programming

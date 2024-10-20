#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <windows.h>
#include <iostream>

typedef struct RGB {
    unsigned int r, g, b;
} RGB;

typedef struct RGB_F {
    float r, g, b;
} RGB_F;

typedef struct Vertex {
    unsigned int x, y;
    RGB color;
    float opacity;
} Vertex;

typedef struct Vertex_F {
    float x, y;
    RGB_F rgb;
    float opacity;
} Vertex_F;

typedef struct color_F {
    RGB_F color;
    float opacity;
} color_F;

void triangle(unsigned int* triangle_ptr, Vertex_F v1_f, Vertex_F v2_f, Vertex_F v3_f);
void clear(unsigned int* clear_ptr, color_F color);
void W32G_SET_DIMENSIONS(unsigned int width, unsigned int height);
unsigned int gen_line(std::vector<Vertex>& line, Vertex start, Vertex end);

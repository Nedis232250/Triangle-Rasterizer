#pragma once
#include "rasterizer.h"

unsigned int rgbtoh(RGB rgb) {
    if (rgb.r > 255) {
        rgb.r = 255;
    }

    if (rgb.b > 255) {
        rgb.b = 255;
    }

    if (rgb.b > 255) {
        rgb.b = 255;
    }

    return (unsigned int)(0xFF * ((float)rgb.b / 255) + 0xFF00 * ((float)rgb.g / 255) + 0xFF0000 * ((float)rgb.r / 255));
}

RGB glrgbtorgb(RGB_F rgbf) {
    if (rgbf.r > 1.0f) {
        rgbf.r = 1.0f;
    }

    if (rgbf.b > 1.0f) {
        rgbf.b = 1.0f;
    }

    if (rgbf.b > 1.0f) {
        rgbf.b = 1.0f;
    }

    return { (unsigned int)(rgbf.r * 255), (unsigned int)(rgbf.g * 255), (unsigned int)(rgbf.b * 255) };
}

Vertex gltoss(Vertex_F vertex, unsigned int sw, unsigned int sh) {
    vertex.x += 1;
    vertex.y += 1;
    vertex.y /= 2;
    vertex.x /= 2;

    return { (unsigned int)(vertex.x * sw), (unsigned int)(vertex.y * sh), glrgbtorgb(vertex.rgb), vertex.opacity };
}

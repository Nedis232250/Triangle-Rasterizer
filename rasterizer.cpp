#include "rasterizer.h"
#include "conversions.h"

unsigned int sw = 0;
unsigned int sh = 0;

void W32G_SET_DIMENSIONS(unsigned int width, unsigned int height) {
    sw = width;
    sh = height;
}

unsigned int gen_line(std::vector<Vertex>& line, Vertex start, Vertex end) {
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    unsigned int steps = max(abs(dx), abs(dy));
    float x = (float)start.x;
    float y = (float)start.y;
    unsigned int cy = start.y;
    unsigned int cx = start.x;
    int yt = 0;
    int xt = 0;

    if (start.y > end.y) {
        yt = -1;
    } else {
        yt = 1;
    }

    if (start.x > end.x) {
        xt = 1;
    } else {
        xt = -1;
    }

    start.opacity *= 255;
    end.opacity *= 255;

    if (dx > dy) {
        for (unsigned int i = 0; i <= steps; i++) {
            if (y != cy) {
                line.push_back({ (unsigned int)x, (unsigned int)(y + yt), { (unsigned int)(start.color.r * (float)(steps - i) / steps + end.color.r * (float)i / steps),
                                                                            (unsigned int)(start.color.g * (float)(steps - i) / steps + end.color.g * (float)i / steps),
                                                                            (unsigned int)(start.color.b * (float)(steps - i) / steps + end.color.b * (float)i / steps),
                }, (float)(start.opacity * (float)(steps - i) / steps + end.opacity * (float)(i / steps)) });
            }

            line.push_back({ (unsigned int)x, (unsigned int)y, { (unsigned int)(start.color.r * (float)(steps - i) / steps + end.color.r * (float)i / steps),
                                                                 (unsigned int)(start.color.g * (float)(steps - i) / steps + end.color.g * (float)i / steps),
                                                                 (unsigned int)(start.color.b * (float)(steps - i) / steps + end.color.b * (float)i / steps),
            }, (float)(start.opacity * (float)(steps - i) / steps + end.opacity * (float)(i / steps)) });

            x += dx / (float)steps;
            y += dy / (float)steps;
            cy = (unsigned int)y;
        }

        return 0;
    }

    for (unsigned int i = 0; i <= steps; i++) {
        if (y != cx) {
            line.push_back({ (unsigned int)(x + xt), (unsigned int)y, { (unsigned int)(start.color.r * (float)(steps - i) / steps + end.color.r * (float)i / steps),
                                                                        (unsigned int)(start.color.g * (float)(steps - i) / steps + end.color.g * (float)i / steps),
                                                                        (unsigned int)(start.color.b * (float)(steps - i) / steps + end.color.b * (float)i / steps),
            }, (float)(start.opacity * (float)(steps - i) / steps + end.opacity * (float)(i / steps)) });
        }

        line.push_back({ (unsigned int)x, (unsigned int)y, { (unsigned int)(start.color.r * (float)(steps - i) / steps + end.color.r * (float)i / steps),
                                                             (unsigned int)(start.color.g * (float)(steps - i) / steps + end.color.g * (float)i / steps),
                                                             (unsigned int)(start.color.b * (float)(steps - i) / steps + end.color.b * (float)i / steps),
        }, (float)(start.opacity * (float)(steps - i) / steps + end.opacity * (float)(i / steps)) });

        x += dx / (float)steps;
        y += dy / (float)steps;
        cx = (unsigned int)x;
    }

    return 0;
}

void triangle(unsigned int* triangle_ptr, Vertex_F v1_f, Vertex_F v2_f, Vertex_F v3_f) {
    unsigned int color = 0;
    Vertex v1 = gltoss(v1_f, sw, sh);
    Vertex v2 = gltoss(v2_f, sw, sh);
    Vertex v3 = gltoss(v3_f, sw, sh);

    std::vector<Vertex> line1;
    std::vector<Vertex> line2;
    std::vector<Vertex> line3;
    std::vector<Vertex> triangle;

    gen_line(line1, v1, v2);

    for (const auto& v : line1) {
        gen_line(triangle, v, v3);
    }
    
    for (int i = 0; i < triangle.size(); i++) {
        if (triangle[i].x < max(v1.x, max(v2.x, v3.x)) && triangle[i].x > min(v1.x, min(v2.x, v3.x)) && triangle[i].y < max(v1.y, max(v2.y, v3.y)) && triangle[i].y > min(v1.y, min(v2.y, v3.y))) {
            triangle_ptr[triangle[i].y * sw + triangle[i].x - 1] = (float)rgbtoh(triangle[i].color);
        }
    }
}

void clear(unsigned int* clear_ptr, color_F color) {
    for (unsigned int i = 0; i < sw * sh; i++) {
        clear_ptr[i] = rgbtoh(glrgbtorgb(color.color));
    }
}

#pragma once
#pragma once
#include "Monument.hpp"
void generateSquareVertices(Monument* m) {
    float width = 25.0f;
    float heigth = 25.0f;
    m->vertices = {
         m->x,      m->y,     m->z,   0.0f,   1.0f,
         m->x + width,  m->y,     m->z,   1.0f,   1.0f,
         m->x + width,  m->y + heigth, m->z,   1.0f,   0.0f,
         m->x,      m->y + heigth, m->z,   0.0f,   0.0f
    };

    m->indices = {
    0, 1, 2,  
    0, 2, 3   
    };
}
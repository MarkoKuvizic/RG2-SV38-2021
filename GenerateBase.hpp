#pragma once
#pragma once
#include "Monument.hpp"
void generateBaseVertices(Monument* m) {
    m->vertices = {
        -0.75f, -0.75f, 1.0f,   0.0f, 0.0f, 
        0.75f, -0.75f, 1.0f,   1.0f, 0.0f,  
        0.75f,  0.75f, 1.0f,   1.0f, 1.0f,  
        -0.75f,  0.75f, 1.0f,   0.0f, 1.0f, 

        -0.75f, -0.75f, 0.0f,   0.25f, 0.25f,  
        0.75f, -0.75f, 0.0f,   0.75f, 0.25f,  
        0.75f,  0.75f, 0.0f,   0.75f, 0.75f,  
        -0.75f,  0.75f, 0.0f,   0.25f, 0.75f  
    };

    m->indices = {
        
        0, 1, 2,
        0, 2, 3,

        4, 6, 5,
        4, 7, 6,

        0, 1, 5,
        0, 5, 4,

        1, 2, 6,
        1, 6, 5,

        2, 3, 7,
        2, 7, 6,

        3, 0, 4,
        3, 4, 7
    };

    for (size_t i = 0; i < m->vertices.size(); i += 5) {
        m->vertices[i + 0] += m->x;
        m->vertices[i + 1] += m->y;
        m->vertices[i + 2] += m->z;
    }
}
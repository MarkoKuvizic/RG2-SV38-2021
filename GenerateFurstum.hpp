#pragma once
#include "Monument.hpp"
void generateFurstumVertices(Monument* m) {
    m->vertices = {
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,

    -0.25f, -0.25f, 1.0f,   0.25f, 0.25f,  
     0.25f, -0.25f, 1.0f,   0.75f, 0.25f,  
     0.25f,  0.25f, 1.0f,   0.75f, 0.75f,  
    -0.25f,  0.25f, 1.0f,   0.25f, 0.75f   
    };

    m->indices = {
        0, 2, 1,
        0, 3, 2,

        4, 5, 6,
        4, 6, 7,

        0, 5, 1,
        0, 4, 5,

        1, 6, 2,
        1, 5, 6,

        2, 7, 3,
        2, 6, 7,

        3, 4, 0,
        3, 7, 4
    };


    for (size_t i = 0; i < m->vertices.size(); i += 5) {
        m->vertices[i + 0] += m->x; 
        m->vertices[i + 1] += m->y; 
        m->vertices[i + 2] += m->z; 
    }
}
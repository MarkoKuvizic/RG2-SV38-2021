#pragma once
#pragma once
#pragma once
#include "Monument.hpp"
void generateFloorVertices(Monument* m) {
    m->vertices = {
        -15.0f, -15.0f, 0.0f,   0.0f, 0.0f, 
        15.0f, -15.0f, 0.0f,   1.0f, 0.0f,  
        15.0f,  15.0f, 0.0f,   1.0f, 1.0f,  
        -15.0f,  15.0f, 0.0f,   0.0f, 1.0f,  
        };

    m->indices = {
        0, 1, 2,
        0, 2, 3
    };

    for (size_t i = 0; i < m->vertices.size(); i += 5) {
        m->vertices[i + 0] += m->x; 
        m->vertices[i + 1] += m->y; 
        m->vertices[i + 2] += m->z; 
    }
}
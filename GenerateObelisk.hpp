#pragma once
#include "Monument.hpp"

void generateObeliskVertices(Monument* m) {

    m->vertices = {
        
         0.0f,  0.0f,  1.5f,   0.25f, 0.25f,  

         -0.25f, -0.25f, 1.0f,   0.0f, 0.0f,
          0.25f, -0.25f, 1.0f,   1.0f, 0.0f,
          0.25f,  0.25f, 1.0f,   1.0f, 1.0f,
         -0.25f,  0.25f, 1.0f,   0.0f, 1.0f,

         -0.3f, -0.3f, -1.5f,   0.0f, 0.0f,
          0.3f, -0.3f, -1.5f,   0.25f, 0.0f,
          0.3f,  0.3f, -1.5f,   0.25f, 0.25f,
         -0.3f,  0.3f, -1.5f,   0.0f, 0.25f,

         -0.6f, -0.6f, -1.5f,   0.0f, 0.0f,
          0.6f, -0.6f, -1.5f,   0.25f, 0.0f,
          0.6f,  0.6f, -1.5f,   0.25f, 0.25f,
         -0.6f,  0.6f, -1.5f,   0.0f, 0.25f,

         };

    for (size_t i = 0; i < m->vertices.size(); i += 5) {
        m->vertices[i + 0] += m->x; 
        m->vertices[i + 1] += m->y; 
        m->vertices[i + 2] += m->z; 
    }

    m->indices = {
        0, 1, 2,  
        0, 2, 3,  
        0, 3, 4,  
        0, 4, 1,  

        1, 2, 6,  1, 6, 5, 
        2, 3, 7, 2, 7, 6,  
        3, 4, 8, 3, 8, 7,  
        4, 1, 5, 4, 5, 8,   



    };
    
}
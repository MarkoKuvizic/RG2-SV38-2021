#pragma once
#include "Monument.hpp"
#include <glm/ext/vector_float3.hpp>

void generateMonument2Vertices(Monument* m) {
    float bx = m->x, by = m->y, bz = m->z; 

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    unsigned int index = 0;
    
    //Donja piramida (ona odsecena sto lici na stepenice)

    float h1 = 1.0f;
    float bottom = -h1 + bz;
    float top = bz;

    float b = 0.6f;  
    float B = 1.2f;  

    std::vector<glm::vec3> frustumTop = {
        { -b, -b, top },
        {  b, -b, top },
        {  b,  b, top },
        { -b,  b, top },
    };
    std::vector<glm::vec3> frustumBottom = {
        { -B, -B, bottom },
        {  B, -B, bottom },
        {  B,  B, bottom },
        { -B,  B, bottom },
    };

    for (auto& v : frustumTop) {
        vertices.insert(vertices.end(), { bx + v.x, by + v.y, v.z, v.x/10, v.y/10 });
    }
    for (auto& v : frustumBottom) {
        vertices.insert(vertices.end(), { bx + v.x, by + v.y, v.z, v.x/10, v.y/10 });
    }

    std::vector<std::pair<int, int>> quads = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}
    };

    for (size_t q = 0; q < quads.size(); ++q) {
        unsigned int i1 = quads[q].first;
        unsigned int i2 = quads[q].second;
        indices.insert(indices.end(), {
            i1, i2, i2 + 4,
            i1, i2 + 4, i1 + 4
            });
    }

    
    indices.insert(indices.end(), {
        0, 1, 2,  0, 2, 3,
        4, 6, 5,  4, 7, 6
        });

    index += 8;


    float p = 0.1f; 
    float ph = 0.5f;

    //Stubovi izmedju baze i vrha

    std::vector<glm::vec3> pillarBases = {
        {-b, -b, top}, {b - 2 * p, -b, top},
        {b - 2 * p, b - 2 * p, top}, {-b, b - 2 * p, top}
    };

    for (auto& base : pillarBases) {
        float x = bx + base.x;
        float y = by + base.y;
        float z = base.z;

        std::vector<glm::vec3> box = {
            {x,     y,     z},
            {x + p,   y,     z},
            {x + p,   y + p,   z},
            {x,     y + p,   z},
            {x,     y,     z + ph},
            {x + p,   y,     z + ph},
            {x + p,   y + p,   z + ph},
            {x,     y + p,   z + ph},
        };

        for (auto& v : box)
            vertices.insert(vertices.end(), { v.x, v.y, v.z, 0.5f, 0.5f });

        std::vector<unsigned> face = {
            0, 1, 2,  0, 2, 3,  
            4, 6, 5,  4, 7, 6,  
            0, 4, 5,  0, 5, 1,
            1, 5, 6,  1, 6, 2,
            2, 6, 7,  2, 7, 3,
            3, 7, 4,  3, 4, 0
        };
        for (auto& i : face)
            indices.push_back(index + i);

        index += 8;
    }


    glm::vec3 tip = { bx, by, bz + ph };
    std::vector<glm::vec3> baseTop = {
        {-b, -b, top + ph},
        { b, -b, top + ph},
        { b,  b, top + ph},
        {-b,  b, top + ph}
    };

    for (auto& v : baseTop)
        vertices.insert(vertices.end(), { bx + v.x, by + v.y, v.z, 0.0f, 0.0f });
    vertices.insert(vertices.end(), { tip.x, tip.y, tip.z + 0.5f, 0.5f, 1.0f });

    unsigned int baseStart = index;
    index += 5;

    indices.insert(indices.end(), {
        baseStart, baseStart + 1, index - 1,
        baseStart + 1, baseStart + 2, index - 1,
        baseStart + 2, baseStart + 3, index - 1,
        baseStart + 3, baseStart,   index - 1,
        baseStart, baseStart + 1, baseStart + 2,
        baseStart, baseStart + 2, baseStart + 3
        });

    m->vertices = vertices;
    m->indices = indices;
}

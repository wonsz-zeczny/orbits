#include "shapes/Sphere.hpp"

#include <cmath>
#include <numbers>

#include <glad/gl.h>
#include <glm/glm.hpp>


using namespace shapes;


Sphere::Sphere() {
    glGenVertexArrays(1, &sphere_vao);
    glGenVertexArrays(1, &lines_vao);

    glGenBuffers(1, &sphere_ebo);
    glGenBuffers(1, &lines_ebo);
    glGenBuffers(1, &vbo);

    calculateVertices();
}

void Sphere::clearMemory(){
    vertices_data.clear();
    indices.clear();
    line_indices.clear();
}

void Sphere::loadDataToGPU() const {
    glBindVertexArray(sphere_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(utils::Vertex) * vertices_data.size(), vertices_data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(utils::Vertex), (GLvoid*)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(utils::Vertex), (GLvoid*)(offsetof(utils::Vertex, normal)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(utils::Vertex), (GLvoid*)(offsetof(utils::Vertex, tex_coords)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(lines_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lines_ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * line_indices.size(), line_indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(utils::Vertex), (GLvoid*)(0));

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Sphere::configureGeometry(unsigned int stack_count, unsigned int sector_count, float radius) {
    stack_count = stack_count;
    sector_count = sector_count;
    radius = radius;

    calculateVertices();
}

void Sphere::calculateVertices() {
    clearMemory();

    float length_inverse = 1.0f / radius;

    float sector_step = 2 * std::numbers::pi / sector_count;
    float stack_step = std::numbers::pi / stack_count;

    for (auto i{ 0 }; i <= stack_count; ++i)
    {
        float stack_angle{ static_cast<float>(std::numbers::pi / 2 - i * stack_step) };        // starting from pi/2 to -pi/2
        float xy{ radius * cosf(stack_angle) };                                 //  r * cos(u)
        float z{ radius * sinf(stack_angle) };                                //    r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (auto j{ 0 }; j <= sector_count; ++j)
        {
            utils::Vertex v;

            float sector_angle{ j * sector_step };           // starting from 0 to 2pi

            // vertex position
            float x{ xy * cosf(sector_angle) };             // r * cos(u) * cos(v)
            float y{ xy * sinf(sector_angle) };             // r * cos(u) * sin(v)

            // normalized vertex normal
            float nx{ x * length_inverse };
            float ny{ y * length_inverse };
            float nz{ z * length_inverse };

            // vertex tex coord between [0, 1]
            float s{ static_cast<float>(j) / sector_count };
            float t{ static_cast<float>(i) / stack_count };

            v.position.x = x;
            v.position.y = y;
            v.position.z = z;

            v.normal.x = nx;
            v.normal.y = ny;
            v.normal.z = nz;

            v.tex_coords.s = s;
            v.tex_coords.t = t;

            vertices_data.push_back(std::move(v));
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;

    for (int i = 0; i < stack_count; ++i)
    {
        k1 = i * (sector_count + 1);     // beginning of current stack
        k2 = k1 + sector_count + 1;      // beginning of next stack

        for (int j = 0; j < sector_count; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0) {
                indices.insert(indices.end(), { k1, k2, k1 + 1 });   // k1---k2---k1+1
            }

            if (i != (stack_count - 1)) {
                indices.insert(indices.end(), { k1 + 1, k2, k2 + 1 }); // k1+1---k2---k2+1
            }

            // vertical lines for all stacks
            line_indices.insert(line_indices.end(), { k1, k2 });

            if (i != 0) { // horizontal lines except 1st stack
                line_indices.insert(line_indices.end(), { k1, k1 + 1 });
            }
        }
    }

    loadDataToGPU();
}

void Sphere::draw() const {
    glBindVertexArray(sphere_vao);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid*)(0));
    
    glBindVertexArray(0);
}

void Sphere::drawLinesOnSphere() const {
    glBindVertexArray(lines_vao);

    glDrawElements(GL_LINES, line_indices.size(), GL_UNSIGNED_INT, (GLvoid*)(0));

    glBindVertexArray(0);
}
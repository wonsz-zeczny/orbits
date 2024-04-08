#include "Sphere.hpp"

#include <cmath>
#include <numbers>

#include <glad/gl.h>
#include <glm/glm.hpp>


Sphere::Sphere() {
    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &ebo);
    glGenBuffers(1, &vbo);
}

void Sphere::clearMemory(){
    vertices_data.clear();
}

void Sphere::loadDataToGPU() const {
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(utils::Vertex) * vertices_data.size(), vertices_data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(utils::Vertex), (GLvoid*)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(utils::Vertex), (GLvoid*)(offsetof(utils::Vertex, normal)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(utils::Vertex), (GLvoid*)(offsetof(utils::Vertex, tex_coords)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Sphere::calculateVertices(unsigned int stack_count, unsigned int sector_count, float radius) {
    clearMemory();

    glm::vec3 vertex_pos;
    float tex_coord_t;
    
    double length_inverse{1.0 / radius};

    double stack_step{std::numbers::pi / stack_count};
    double sector_step{2 * std::numbers::pi / sector_count};
    
    double stack_angle;
    double sector_angle;

    for(auto i{0}; i <= stack_count; ++i) {
        utils::Vertex v;

        stack_angle = (std::numbers::pi / 2) - i * stack_step;

        tex_coord_t = static_cast<float>(i) / stack_count;

        for(auto j{0}; j <= sector_count; ++j) {
            sector_angle = j * sector_step;

            vertex_pos.x = radius * cos(stack_angle) * cos(sector_angle);
            vertex_pos.y = radius * cos(stack_angle) * sin(sector_angle);

            v.position.x = radius * cos(stack_angle) * cos(sector_angle);
            v.position.y = radius * cos(stack_angle) * sin(sector_angle);
            v.position.z = radius * sin(stack_angle);

            v.normal.x = v.position.x * length_inverse;
            v.normal.y = v.position.y * length_inverse;
            v.normal.z = v.position.z * length_inverse;

            v.tex_coords.s = static_cast<float>(j) / sector_count;
            v.tex_coords.t = tex_coord_t;
        }

        vertices_data.push_back(std::move(v));
    }

    unsigned int stack_top_left_index;
    unsigned int stack_bottom_left_index;

    for(auto i{0}; i < stack_count; ++i) {
        stack_top_left_index = i * (sector_count + 1); // Current stack beginning
        stack_bottom_left_index = stack_top_left_index + sector_count + 1; // Next stack beginning

        for(auto j{0}; j < sector_count; ++j, ++stack_top_left_index, ++stack_bottom_left_index) {

            if(i != 0){
                indices.push_back(stack_top_left_index);
                indices.push_back(stack_bottom_left_index);
                indices.push_back(stack_top_left_index + 1);
            }

            if(i != (stack_count - 1)) {
                indices.push_back(stack_top_left_index + 1);
                indices.push_back(stack_bottom_left_index);
                indices.push_back(stack_bottom_left_index + 1);
            }

            // Vertical lines k1 => k2
            line_indices.push_back(stack_top_left_index);
            line_indices.push_back(stack_bottom_left_index);

            // Horizontal lines k1 => k1 + 1
            if(i != 0) {
                line_indices.push_back(stack_top_left_index);
                line_indices.push_back(stack_top_left_index + 1);
            }
        }
    }

    loadDataToGPU();
}

void Sphere::draw() const {
    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
    
    glBindVertexArray(0);
}
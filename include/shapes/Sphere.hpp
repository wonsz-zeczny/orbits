#pragma once

#include "Utils.hpp"
#include "Texture.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <string_view>


namespace shapes {
    struct ShapeOrientationData {
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 initial_rotation_axis{ 1.0f };
        float initial_rotation_degrees{ 0.0f };
        float distance_from_origin;
    };

    class Sphere {
        public:
            Sphere(std::string_view texture_filepath, std::string_view texture_uniform_name,
                ShapeOrientationData&& shape_orientation_data);

            void configureGeometry(unsigned int stack_count, unsigned int sector_count, float radius);
            void calculateVertices();
            void draw() const;
            void drawLinesOnSphere() const;
            glm::vec3 getPosition() const;

        private:
            void clearMemory();
            void loadDataToGPU() const;

            std::vector<utils::Vertex> vertices_data{};
            std::vector<unsigned int> indices{};
            std::vector<unsigned int> line_indices{};

            Texture texture;

            unsigned int stack_count{36};
            unsigned int sector_count{72};
            float radius{2.0f};

            ShapeOrientationData shape_orientation_data;

            unsigned int sphere_vao{};
            unsigned int lines_vao{};
            unsigned int sphere_ebo{};
            unsigned int lines_ebo{};
            unsigned int vbo{};
    };
}

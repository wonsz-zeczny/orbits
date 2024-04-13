#pragma once

#include "Utils.hpp"

#include <vector>


namespace shapes {
    class Sphere {
        public:
            Sphere();

            void configureGeometry(unsigned int stack_count, unsigned int sector_count, float radius);
            void calculateVertices();
            void draw() const;
            void drawLinesOnSphere() const;

        private:
            void clearMemory();
            void loadDataToGPU() const;

            std::vector<utils::Vertex> vertices_data{};
            std::vector<unsigned int> indices{};
            std::vector<unsigned int> line_indices{};

            unsigned int stack_count{18};
            unsigned int sector_count{36};
            float radius{1.0f};

            unsigned int sphere_vao{};
            unsigned int lines_vao{};
            unsigned int sphere_ebo{};
            unsigned int lines_ebo{};
            unsigned int vbo{};
    };
}

#pragma once

#include "Utils.hpp"

#include <vector>


class Sphere {
    public:
        Sphere();

        void calculateVertices(unsigned int stack_count, unsigned int sector_count, float radius);
        void draw() const;

    private:
        void clearMemory();
        void loadDataToGPU() const;

        std::vector<Vertex> vertices_data{};
        std::vector<unsigned int> indices{};
        std::vector<unsigned int> line_indices{};

        unsigned int vao;
        unsigned int ebo;
        unsigned int vbo;
};
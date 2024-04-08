#pragma once

#include <glm/glm.hpp>

namespace utils {
    constexpr float SCREEN_WIDTH{ 800.0f };
    constexpr float SCREEN_HEIGHT{ 600.0f };

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 tex_coords;
    };
}

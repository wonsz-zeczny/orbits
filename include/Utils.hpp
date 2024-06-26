#pragma once

#include <glm/glm.hpp>

#define SHADERS_DIR "C:/Users/Darek/Desktop/Programowanie/orbits/shaders/"
#define RESOURCES_DIR "C:/Users/Darek/Desktop/Programowanie/orbits/resources/"


namespace utils {
    constexpr float SCREEN_WIDTH{ 800.0f };
    constexpr float SCREEN_HEIGHT{ 600.0f };

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 tex_coords;
    };
}

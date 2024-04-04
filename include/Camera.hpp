#pragma once

#include <glm/glm.hpp>


class Camera {
    public:
        

    private:
        glm::vec3 position{0.0f, 0.0f, 0.0f};
        glm::vec3 direction{0.0f, 0.0f, -1.0f};
        glm::vec3 world_up{0.0f, 1.0f, 0.0f};

        float yaw{0.0f};
        float pitch{0.0f};
        float speed{5.0f};
        float zoom{0.0f};
        float mouse_sensitivity{0.5f};
};
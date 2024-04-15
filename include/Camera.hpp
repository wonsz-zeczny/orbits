#pragma once

#include <glm/glm.hpp>


namespace camera {

enum class Direction {
    Forward,
    Left,
    Right,
    Backward
};

class Camera {
    public:
        Camera() = delete;

        static void processCameraMovement(Direction movement_direction, float deltatime);
        static void processCameraRotation(float x_offset, float y_offset);
        static void processCameraZoom(float offset);

        static float getZoom();
        static glm::mat4 getLookAtMatrix();
        static glm::vec3 getPosition();
        static glm::vec3 getDirection();

        static void updateCameraVectors();

    private:

        static inline glm::vec3 position{ 0.0f, 0.0f, 0.0f };
        static inline glm::vec3 direction{ 0.0f, 0.0f, -1.0f };
        static inline glm::vec3 world_up{ 0.0f, 1.0f, 0.0f };
        static inline glm::vec3 right{};
        static inline glm::vec3 up{};

        static inline float yaw{ -90.0f };
        static inline float pitch{ 0.0f };
        static inline float speed{ 5.0f };
        static inline float zoom{ 45.0f };
        static inline float mouse_sensitivity{ 0.2f };
    };
}


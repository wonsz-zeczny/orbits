#include "Init.hpp"
#include "Utils.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Program.hpp"
#include "planetary-system/CelestialBody.hpp"
#include "planetary-system/PlanetarySystem.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>


void processKeyboardInput(GLFWwindow* window) {
    static float deltatime{ 0.0f };
    static float last_frame_time{ 0.0f };

    float current_time{ static_cast<float>(glfwGetTime()) };

    deltatime = current_time - last_frame_time;
    last_frame_time = current_time;

    float camera_speed{ 2.5f * deltatime };

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera::Camera::processCameraMovement(camera::Direction::Forward, deltatime);
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera::Camera::processCameraMovement(camera::Direction::Left, deltatime);
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera::Camera::processCameraMovement(camera::Direction::Backward, deltatime);
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera::Camera::processCameraMovement(camera::Direction::Right, deltatime);
    }
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void processMouseMovement(GLFWwindow* window, double x_pos, double y_pos) {
    static double previous_x_pos{ utils::SCREEN_WIDTH / 2 };
    static double previous_y_pos{ utils::SCREEN_HEIGHT / 2 };

    double x_offset{ x_pos - previous_x_pos};
    double y_offset{ previous_y_pos - y_pos };

    previous_x_pos = x_pos;
    previous_y_pos = y_pos;

    camera::Camera::processCameraRotation(x_offset, y_offset);
}

void processMouseScroll(GLFWwindow* window, double x_offset, double y_offset) {
    camera::Camera::processCameraZoom(y_offset);
}

int main() {

    spdlog::set_level(spdlog::level::debug);

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    glfwSetErrorCallback([](int e, const char* msg){
        spdlog::error("GLFW ERROR:\nErorr code: {}\nMessage: {}", e, msg);
    });

    GLFWwindow* window{glfwCreateWindow(utils::SCREEN_WIDTH, utils::SCREEN_HEIGHT, "Orbits", nullptr, nullptr)};

    if(window == nullptr) {
        spdlog::error("Cannot create a GLFW window!");
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, processMouseMovement);

    glfwSetScrollCallback(window, processMouseScroll);

    if(!gladLoadGL(glfwGetProcAddress)) {
        spdlog::error("Cannot load OpenGL functions!");

        return -1;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
    });

    glViewport(0, 0, utils::SCREEN_WIDTH, utils::SCREEN_HEIGHT);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEPTH_TEST);

    glDebugMessageCallback(debugOpenGLMessageCallback, nullptr);

    Program sphere_program;
    Program lines_program;

    {
        Shader sphere_vertex_shader{GL_VERTEX_SHADER};
        sphere_vertex_shader.loadShaderCode(SHADERS_DIR"sphere-vertex.glsl");

        Shader sphere_fragment_shader{GL_FRAGMENT_SHADER};
        sphere_fragment_shader.loadShaderCode(SHADERS_DIR"sphere-fragment.glsl");

        sphere_vertex_shader.compileShaderCode();
        sphere_fragment_shader.compileShaderCode();

        sphere_program.attachShader(sphere_vertex_shader.getShaderID());
        sphere_program.attachShader(sphere_fragment_shader.getShaderID());

        Shader lines_vertex_shader{ GL_VERTEX_SHADER };
        lines_vertex_shader.loadShaderCode(SHADERS_DIR"lines-vertex.glsl");

        Shader lines_fragment_shader{ GL_FRAGMENT_SHADER };
        lines_fragment_shader.loadShaderCode(SHADERS_DIR"lines-fragment.glsl");

        lines_vertex_shader.compileShaderCode();
        lines_fragment_shader.compileShaderCode();

        lines_program.attachShader(lines_vertex_shader.getShaderID());
        lines_program.attachShader(lines_fragment_shader.getShaderID());
    }
    
    sphere_program.link();
    lines_program.link();
    
    planetary_system::PlanetarySystem solar_system;

    //solar_system.addCelestialBody(planetary_system::CelestialBody{
    //    planetary_system::CelestialBodyParams{
    //            .name = "Sun",
    //            .texture_filepath = RESOURCES_DIR"sun-texture.jpg",
    //            .radius_km = 696340.0f,
    //            .distance_from_star_au = 0,
    //            .axial_tilt_degrees = 7.25f,
    //            .rotation_speed_kmh = 7189.0f,
    //            .orbital_speed_kmh = 0.0f,
    //            .shape_orientation_data = shapes::ShapeOrientationData{
    //                .position = glm::vec3{0.0f},
    //                .direction = glm::vec3{0.0f, 0.0f, 1.0f},
    //            }
    //        }
    //    });

    solar_system.addCelestialBody(planetary_system::CelestialBody{
            planetary_system::CelestialBodyParams{
                    .name = "Earth",
                    .texture_filepath = RESOURCES_DIR"earth-texture.jpg",
                    .radius_km = 6371.0f,
                    .distance_from_star_au = 1.0f,
                    .axial_tilt_degrees = 24.44f,
                    .rotation_speed_kmh = 1670.0f,
                    .orbital_speed_kmh = 107280.0f
            },
            shapes::ShapeOrientationData{
                    .position = glm::vec3{0.0f, 0.0f, 0.0f},
                    .direction = glm::vec3{0.0f, 0.0f, -1.0f},
                    .initial_rotation_axis = glm::vec3{1.0f, 0.0f, 0.0f},
                    .initial_rotation_degrees = -90.0f,
                    .distance_from_origin = 1.0f
            }
        });
    
    while(!glfwWindowShouldClose(window)) {
        processKeyboardInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f),
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        solar_system.draw(sphere_program);
        solar_system.updateCelestialBodiesVectors();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
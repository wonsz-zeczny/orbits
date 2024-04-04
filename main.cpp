#include "Debug.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>


int main() {
    constexpr int WINDOW_WIDTH{800};
    constexpr int WINDOW_HEIGHT{600};

    spdlog::set_level(spdlog::level::debug);

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    glfwSetErrorCallback([](int e, const char* msg){
        spdlog::error("GLFW ERROR:\nErorr code: {}\nMessage: {}", e, msg);
    });

    GLFWwindow* window{glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Orbits", nullptr, nullptr)};

    if(window == nullptr) {
        spdlog::error("Cannot create a GLFW window!");
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGL(glfwGetProcAddress)) {
        spdlog::error("Cannot load OpenGL functions!");

        return -1;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
    });

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEPTH_TEST);

    glDebugMessageCallback(debugMessageCallback, nullptr);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f),
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
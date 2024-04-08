#include "Init.hpp"
#include "Sphere.hpp"
#include "Shader.hpp"
#include "Program.hpp"

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

    glDebugMessageCallback(debugOpenGLMessageCallback, nullptr);

    Program sphere_program;

    {
        Shader vertex_shader{GL_VERTEX_SHADER};
        vertex_shader.loadShaderCode(SHADERS_DIR"sphere-vertex.glsl");

        Shader fragment_shader{GL_FRAGMENT_SHADER};
        fragment_shader.loadShaderCode(SHADERS_DIR"sphere-fragment.glsl");

        vertex_shader.compileShaderCode();
        fragment_shader.compileShaderCode();

        sphere_program.attachShader(vertex_shader.getShaderID());
        sphere_program.attachShader(fragment_shader.getShaderID());
    }
    
    sphere_program.link();

    Sphere sphere;
    sphere.calculateVertices(20, 20, 5.0f);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f),
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sphere_program.use();
        sphere.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
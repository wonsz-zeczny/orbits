#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>


static void APIENTRY debugCallback(
	GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	spdlog::debug("---------------");
	spdlog::debug("Debug message ({}): {}\n", id, message);

    std::string source_str;
    std::string type_str;
    std::string sev_str;

	switch (source)
	{
        case GL_DEBUG_SOURCE_API:             source_str = "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   source_str = "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: source_str = "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     source_str = "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     source_str = "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           source_str = "Source: Other"; break;
	} 

	switch (type)
	{
        case GL_DEBUG_TYPE_ERROR:               type_str = "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_str = "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         type_str = "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         type_str = "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              type_str = "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          type_str = "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           type_str = "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               type_str = "Type: Other"; break;
	} 

	switch (severity)
	{
        case GL_DEBUG_SEVERITY_HIGH:         sev_str = "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       sev_str = "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          sev_str = "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: sev_str = "Severity: notification"; break;
	} 

	spdlog::debug("{}\n {}\n {}\n", source_str, type_str, sev_str);
}

int main() {
    constexpr int WINDOW_WIDTH{800};
    constexpr int WINDOW_HEIGHT{600};

    spdlog::set_level(spdlog::level::debug);

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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

    glDebugMessageCallback(debugCallback, nullptr);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f),
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
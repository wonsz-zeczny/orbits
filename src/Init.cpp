#include "Init.hpp"

#include <spdlog/spdlog.h>


void APIENTRY debugOpenGLMessageCallback(
	GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam) {

	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	spdlog::debug("---------------");
	spdlog::debug("Debug message ({}): {}\n", id, message); 

    std::string source_str;
    std::string type_str;
    std::string sev_str;

	switch (source) {
        case GL_DEBUG_SOURCE_API:             source_str = "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   source_str = "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: source_str = "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     source_str = "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     source_str = "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           source_str = "Source: Other"; break;
	} 

	switch (type) {
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

	switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         sev_str = "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       sev_str = "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          sev_str = "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: sev_str = "Severity: notification"; break;
	} 

	spdlog::debug("{}\n{}\n{}\n", source_str, type_str, sev_str);
}
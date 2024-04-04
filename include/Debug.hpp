#include <glad/gl.h>
#include <GLFW/glfw3.h>


void APIENTRY debugMessageCallback(	
    GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam);
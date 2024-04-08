#include "Program.hpp"

#include <spdlog/spdlog.h>

#include <glm/gtc/type_ptr.hpp>


void Program::attachShader(unsigned int shader_id) const {
    glAttachShader(id, shader_id);
}

void Program::link() const {
    glLinkProgram(id);

    printLinkingLogs();
}

void Program::use() const {
    glUseProgram(id);
}

unsigned int Program::getProgramID() const {
    return id;
}

void Program::setMatrix4fv(const char* name, const glm::mat4& matrix) {
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::printLinkingLogs() const {
    int success;
	char info_log[1024];
	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(id, sizeof(info_log), nullptr, info_log);
		spdlog::error("ERROR::PROGRAM::LINKING_FAILED\n{}\n", info_log);
	}
}
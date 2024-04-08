#include "Shader.hpp"

#include <sstream>
#include <fstream>
#include <filesystem>

#include <spdlog/spdlog.h>


Shader::Shader(GLenum shader_type) : id{glCreateShader(shader_type)}, shader_type{shader_type} {}

Shader::~Shader() {
    glDeleteShader(id);
}

void Shader::loadShaderCode(const std::string& shader_filepath) {
    if(!std::filesystem::exists(shader_filepath)){
        spdlog::error("Shader file doesn't exists: {}", shader_filepath);
        return;
    }

    std::ifstream shader_file_content{shader_filepath};
    std::ostringstream oss;

    oss << shader_file_content.rdbuf();

    shader_code = oss.str();
}

void Shader::compileShaderCode() const {
    const char* shader_code_ptr{shader_code.c_str()};

    glShaderSource(id, 1, &shader_code_ptr, nullptr);
    glCompileShader(id);

    printCompilationLogs();
}

unsigned int Shader::getShaderID() const {
    return id;
}

void Shader::printCompilationLogs() const {
    int success;
	char info_log[1024];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(id, sizeof(info_log), nullptr, info_log);
		spdlog::error("ERROR::SHADER::{}::COMPILATION_FAILED\n{}\n", shader_type, info_log);
	}
}
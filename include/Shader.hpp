#pragma once

#include <string>

#include <glad/gl.h>


class Shader {
    public:
        Shader(GLenum shader_type);
        ~Shader();

        void loadShaderCode(const std::string& shader_filepath);
        void compileShaderCode() const;

        unsigned int getShaderID() const;

    private:
        void printCompilationLogs() const;

        unsigned int id{}; 
        GLenum shader_type;
        std::string shader_code;
};
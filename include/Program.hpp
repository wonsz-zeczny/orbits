#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <string_view>


class Program {
    public:
        Program() = default;

        void attachShader(unsigned int shader_id) const;
        void link() const;
        void use() const;

        unsigned int getProgramID() const;

        void setMatrix4fv(std::string_view name, const glm::mat4& matrix) const;

    private:
        void printLinkingLogs() const;
        
        unsigned int id{glCreateProgram()};
};
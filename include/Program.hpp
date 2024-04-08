#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>


class Program {
    public:
        Program() = default;

        void attachShader(unsigned int shader_id) const;
        void link() const;
        void use() const;

        unsigned int getProgramID() const;

        void setMatrix4fv(const char* name, const glm::mat4& matrix);

    private:
        void printLinkingLogs() const;
        
        unsigned int id{glCreateProgram()};
};
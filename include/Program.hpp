#pragma once

#include <glad/gl.h>


class Program {
    public:
        Program() = default;

        void attachShader(unsigned int shader_id) const;
        void link() const;
        void use() const;

        unsigned int getProgramID() const;

    private:
        void printLinkingLogs() const;
        
        unsigned int id{glCreateProgram()};
};
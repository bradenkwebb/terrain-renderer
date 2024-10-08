#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    private:
        void checkCompileErrors(unsigned int shader, std::string type);
    public:
        unsigned int ID; // the program ID

        Shader(const char* vertexPath, const char* fragmentPath);
        void use();

        // utilities
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, glm::mat4 mat) const;
};

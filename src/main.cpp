#include <iostream>
// #include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string getCPPVersion() {
    if (__cplusplus == 202101L) return "C++23";
    else if (__cplusplus == 202002L) return "C++20";
    else if (__cplusplus == 201703L) return "C++17";
    else if (__cplusplus == 201402L) return "C++14";
    else if (__cplusplus == 201103L) return "C++11";
    else if (__cplusplus == 199711L) return "C++98";
    else return "pre-standard C++." + __cplusplus;
}

int main() {
    std::cout << "Hello World!" << std::endl;
    std::cout << "Version: " << getCPPVersion() << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    return 0;
}
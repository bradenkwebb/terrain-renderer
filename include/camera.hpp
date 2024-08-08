#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
private:
    glm::vec3 worldUp;
    glm::vec3 cameraUp;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    const float cameraSpeed = 5.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;
public:
    float fov = 45.0f;
    Camera();
    void processInput(GLFWwindow* window, const float deltaTime);
    glm::mat4 getView();
    void adjustAngle(float xoffset, float yoffset);
};
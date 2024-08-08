#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
private:
    const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f); // constant since gravity shouldn't change
    glm::vec3 cameraUp;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    const float cameraSpeed = 5.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;
public:
    float fov = 45.0f;
    Camera();
    glm::mat4 getView();
    void processKeyboard(CameraMovement direction, const float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(double xoffset, double yoffset);
};
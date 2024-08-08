#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"

Camera::Camera() {
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    glm::vec3 cameraDirection = glm::normalize(cameraPos + cameraFront);
    glm::vec3 cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    adjustAngle(0.0f, 0.0f);
};

glm::mat4 Camera::getView() {
    // Creates the look at matrix as defined here: https://learnopengl.com/Getting-started/Camera
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
};

void Camera::processInput(GLFWwindow* window, const float deltaTime) {
    float speed = this->cameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += speed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= speed * glm::normalize(glm::cross(cameraFront, cameraUp));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += speed * glm::normalize(glm::cross(cameraFront, cameraUp));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= speed * cameraFront;
    }
};

void Camera::adjustAngle(float xoffset, float yoffset) {
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    } else if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
};
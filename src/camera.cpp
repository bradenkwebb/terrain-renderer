#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"

Camera::Camera() {
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    glm::vec3 cameraDirection = glm::normalize(cameraPos + cameraFront);
    glm::vec3 cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    processMouseMovement(0.0f, 0.0f);
};

glm::mat4 Camera::getView() {
    // Creates the look at matrix as defined here: https://learnopengl.com/Getting-started/Camera
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
};

void Camera::processKeyboard(CameraMovement direction, const float deltaTime) {
    float speed = this->cameraSpeed * deltaTime;
    if (direction == FORWARD) {
        cameraPos += speed * cameraFront;
    }
    if (direction == LEFT) {
        cameraPos -= speed * glm::normalize(glm::cross(cameraFront, cameraUp));
    }
    if (direction == RIGHT) {
        cameraPos += speed * glm::normalize(glm::cross(cameraFront, cameraUp));
    }
    if (direction == BACKWARD) {
        cameraPos -= speed * cameraFront;
    }
    cameraPos.y = 0.0f; // keeps the user on the same plane, the "ground"
};

void Camera::processMouseMovement(float xoffset, float yoffset) {
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
    // After changing cameraFront, the right and up vector also need to change to maintain an orthonormal basis
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
};

void Camera::processMouseScroll(double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f) {
        fov = 1.0f;
    }
    if (fov > 45.0f) {
        fov = 45.0f;
    }
}
#define GLM_ENABLE_EXPERIMENTAL
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Camera::Camera()
    : target(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f),
      distance(10.0f), yaw(-90.0f), pitch(20.0f) {
    updatePosition();
}

void Camera::updatePosition() {
    float x = distance * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    float y = distance * sin(glm::radians(pitch));
    float z = distance * cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    position = target + glm::vec3(x, y, z);
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}

void Camera::processMouseMovement(double xOffset, double yOffset) {
    constexpr float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch -= yOffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updatePosition();
}

void Camera::processMouseScroll(double yOffset) {
    distance -= yOffset;
    if (distance < 1.0f) distance = 1.0f;
    if (distance > 50.0f) distance = 50.0f;

    updatePosition();
}

void Camera::processKeyboard(GLFWwindow* window, const double deltaTime) {
    const glm::vec3 direction = glm::normalize(target - position);
    const glm::vec3 right = glm::normalize(glm::cross(direction, up));

    float speed = 15.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        target += direction * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        target -= direction * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        target -= right * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        target += right * speed;
    }

    updatePosition();
}
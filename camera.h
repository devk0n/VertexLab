#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    glm::vec3 position{};
    glm::vec3 target;
    glm::vec3 up;

    double yaw, pitch, distance;

    Camera();
    void updatePosition();
    glm::mat4 getViewMatrix();
    void processMouseMovement(double xOffset, double yOffset);
    void processMouseScroll(double yOffset);
    void processKeyboard(GLFWwindow* window, double deltaTime);
};

#endif

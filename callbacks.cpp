#include "callbacks.h"
#include "camera.h"

extern Camera camera;

bool isMouseButtonDown = false;
bool firstMouse = true;
float lastX = 400, lastY = 300;

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (!isMouseButtonDown) return;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xOffset, yOffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.processMouseScroll(yoffset);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            isMouseButtonDown = true;
        } else if (action == GLFW_RELEASE) {
            isMouseButtonDown = false;
            firstMouse = true;
        }
    }
}

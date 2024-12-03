#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <GLFW/glfw3.h>

extern bool isMouseButtonDown;
extern bool firstMouse;
extern double lastX, lastY;

void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xffset, double yoffset);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

#endif

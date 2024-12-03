#ifndef UTILS_H
#define UTILS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Function declarations
void InitializeGLFW();
GLFWwindow* CreateWindow(int width = 1280, int height = 960, const char* title = "3D Grid Environment");
void InitializeGLEW();
void SetupOpenGLSettings();
void SetupCallbacks(GLFWwindow* window);
void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

#endif // UTILS_H

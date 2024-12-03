#include "utils.h"
#include "callbacks.h"
#include <iostream>

void InitializeGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(-1);
    }
    glfwWindowHint(GLFW_SAMPLES, 16); // Enable 16x anti-aliasing
}

GLFWwindow* CreateWindow(const int width, const int height, const char* title) {
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window\n";
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Disable V-Sync
    return window;
}

void InitializeGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        glfwTerminate();
        exit(-1);
    }
}

void SetupOpenGLSettings() {
    glEnable(GL_MULTISAMPLE);      // Enable anti-aliasing
    glEnable(GL_DEPTH_TEST);       // Enable depth testing
    glEnable(GL_DEBUG_OUTPUT);     // Enable OpenGL debug messages
    glDebugMessageCallback(openglDebugCallback, nullptr);
}

void SetupCallbacks(GLFWwindow* window) {
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    // ANSI color codes
    const char* resetColor = "\033[0m";
    const char* infoColor = "\033[32m";   // Green
    const char* warningColor = "\033[33m"; // Yellow
    const char* errorColor = "\033[31m";  // Red

    const char* color;

    // Select color based on severity
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        color = errorColor;
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        color = warningColor;
        break;
    case GL_DEBUG_SEVERITY_LOW:
    case GL_DEBUG_SEVERITY_NOTIFICATION:
    default:
        color = infoColor; // Use green for notifications
        break;
    }

    // Print the message with the selected color
    std::cerr << color << "OpenGL Debug Message: " << message << resetColor << std::endl;

}


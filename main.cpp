#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Project headers
#include "camera.h"
#include "utils.h"
#include "drawing_utils.h"
#include "imgui.h"
#include "imgui_manager.h"
#include "imgui_widgets.h"

// Global variables
Camera camera;

// Shader source
const char* vertexShaderSource = R"glsl(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)glsl";

const char* fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.3, 1.0);
}
)glsl";

// Utility to compile shaders
GLuint CompileShader(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// Body structure
struct Body {
    glm::vec3 position;
    glm::quat orientation;
    glm::vec3 scale;

    Body(glm::vec3 pos = glm::vec3(0.0f), glm::quat orient = glm::quat(), glm::vec3 scl = glm::vec3(1.0f))
        : position(pos), orientation(orient), scale(scl) {}
};

// Render a simple cube
void DrawCube(GLuint vao, GLuint shaderProgram, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}


int main() {
    // Initialize GLFW and create a window
    InitializeGLFW();
    GLFWwindow* window = CreateWindow();
    if (!window) return -1;

    // Initialize GLEW and setup OpenGL settings
    InitializeGLEW();
    SetupOpenGLSettings();

    // Setup callbacks and initialize ImGui
    SetupCallbacks(window);
    ImGuiManager::Init(window);

    // Create grid and axes
    const GridData grid = CreateGrid();

    // Main render loop
    double lastFrame = 0.0f, fpsTimer = 0.0f;
    int frameCount = 0;
    double fps = 0.0f, frameTime = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        const double currentFrame = glfwGetTime();
        const double deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // FPS calculation
        frameCount++;
        fpsTimer += deltaTime;
        if (fpsTimer >= 1.0f) {
            fps = frameCount / fpsTimer;
            frameTime = (fpsTimer / frameCount) * 1000.0f;
            frameCount = 0;
            fpsTimer = 0.0f;
        }

        // Input handling and ImGui rendering
        camera.processKeyboard(window, deltaTime);
        ImGuiManager::BeginFrame();
        RenderImGuiWidgets(fps, frameTime);
        ImGui::Render();

        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // View and projection matrices
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 960.0f, 0.1f, 100.0f);

        // Draw grid and axes
        DrawGrid(grid, view, projection);

        // Render ImGui and swap buffers
        ImGuiManager::Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    ImGuiManager::Cleanup();
    glDeleteVertexArrays(1, &grid.vao);
    glDeleteBuffers(1, &grid.vbo);
    glDeleteProgram(grid.shaderProgram);
    glfwTerminate();

    return 0;
}

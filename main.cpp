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

    // Create grid
    GridData grid = CreateGrid();

    // Main render loop
    float lastFrame = 0.0f, fpsTimer = 0.0f;
    int frameCount = 0;
    float fps = 0.0f, frameTime = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
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

        // Draw grid
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

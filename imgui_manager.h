#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include <GLFW/glfw3.h>
#include "imgui_manager.h"


class ImGuiManager {
public:
    static void Init(GLFWwindow* window);
    static void BeginFrame();
    static void Render();
    static void Cleanup();
};

#endif // IMGUI_MANAGER_H

#include "imgui_widgets.h"
#include <imgui.h>

void RenderImGuiWidgets(const float fps, const float frameTime) {
    ImGui::Begin("Performance Stats");
    ImGui::Text("FPS: %.1f", fps);
    ImGui::Text("Frame Time: %.2f ms", frameTime);
    ImGui::End();
}

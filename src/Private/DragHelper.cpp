//
// Created by sunny on 2022-11-19.
//

#include "DragHelper.h"
#include "DOM.h"

DragHelper::DragHelper() {
    _style_flag |= ImGuiWindowFlags_NoDecoration;
    _style_flag |= ImGuiWindowFlags_NoResize;
    _style_flag |= ImGuiWindowFlags_NoMove;
    _style_flag |= ImGuiWindowFlags_NoSavedSettings;
    _style_flag |= ImGuiWindowFlags_NoScrollbar;
    _style_flag |= ImGuiWindowFlags_NoBackground;
}

void DragHelper::draw() {
    auto io = ImGui::GetIO();
    ImGui::SetNextWindowPos(io.MousePos, ImGuiCond_Always, ImVec2(0.5, 0.5));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (!ImGui::Begin("Holding Widget", &DOM::drag_shown, _style_flag))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }
    if (ImGui::Button("Button")) {
        DOM::drag_shown = false;
    }
    ImGui::PopStyleVar();
    ImGui::End();
}



/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#include "Toolbox.h"

Toolbox::Toolbox() {
    _style_flag |= ImGuiWindowFlags_NoMove;
    _style_flag |= ImGuiWindowFlags_NoCollapse;
}

void Toolbox::draw() {
    ImGui::SetNextWindowPos(_pos_vec, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(_size_vec, ImGuiCond_FirstUseEver);
    ImGui::Begin(_window_name, nullptr, _style_flag);

    if (ImGui::CollapsingHeader("Basic")) {
        if (ImGui::BeginTable("table_basic", 2)) {
            // Text widget
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::BulletText("Text Label");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("Text");
            // Button widget
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::BulletText("Push Button");
            ImGui::TableSetColumnIndex(1);

            ImGui::Button("Button");
            if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0)) {
                DOM::drag_shown = true;
                // TODO: Type needed.
            } else if (!ImGui::IsMouseDragging(0)) {
                DOM::drag_shown = false;
            }

            ImGui::EndTable();
        }
    }

    ImGui::End();
}

void Toolbox::onCanvasSizeChanged() {
    _size_vec = ImVec2(DOM::width_panel_normal, DOM::canvas_height - DOM::gap_top*2 - DOM::gap_padding - DOM::height_panel_normal);
    ImGui::SetWindowPos(_window_name, _pos_vec, ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(_window_name, _size_vec, ImGuiCond_FirstUseEver);
}
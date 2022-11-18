/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.1
 * Content :
 *   1.Implements banner bar render.
 */

#include "Banner.h"

Banner::Banner() {
    _style_flag |= ImGuiWindowFlags_NoDecoration;
    _style_flag |= ImGuiWindowFlags_NoMove;
    _style_flag |= ImGuiWindowFlags_NoSavedSettings;
}

void Banner::draw() {
    ImGui::SetNextWindowPos(_pos_vec(), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(_size_vec, ImGuiCond_FirstUseEver);
    ImGui::Begin(_window_name, nullptr, _style_flag);
    ImGui::Text("TODO: Draw banner tool panel.");
    ImGui::End();
}

void Banner::onCanvasSizeChanged() {
    _size_vec = ImVec2(DOM::canvas_width - 20, DOM::height_panel_normal);
    ImGui::SetWindowPos(_window_name, _pos_vec(), ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(_window_name, _size_vec, ImGuiCond_FirstUseEver);
}



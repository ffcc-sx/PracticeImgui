/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#include "Toolbox.h"

Toolbox::Toolbox() {
    _style_flag |= ImGuiWindowFlags_NoDecoration;
    _style_flag |= ImGuiWindowFlags_NoMove;
}

void Toolbox::draw() {
    ImGui::SetNextWindowPos(_pos_vec, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(_size_vec, ImGuiCond_FirstUseEver);
    ImGui::Begin(_window_name, nullptr, _style_flag);
    ImGui::Text("TODO: Draw toolbox tool panel.");
    ImGui::End();
}

void Toolbox::onCanvasSizeChanged() {
    _size_vec = ImVec2(DOM::width_panel_normal, DOM::canvas_height - DOM::gap_top*2 - DOM::gap_padding - DOM::height_panel_normal);
    ImGui::SetWindowPos(_window_name, _pos_vec, ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(_window_name, _size_vec, ImGuiCond_FirstUseEver);
}
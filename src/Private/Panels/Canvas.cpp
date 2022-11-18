/*
 * Author  : SunXin
 * Modify  : 2022-11-19
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#include "Canvas.h"

Canvas::Canvas() {
    _style_flag |= ImGuiWindowFlags_NoCollapse;
    _style_flag |= ImGuiWindowFlags_NoMove;
    _style_flag |= ImGuiWindowFlags_NoSavedSettings;
    _style_flag |= ImGuiWindowFlags_NoCollapse;
    _style_flag |= ImGuiWindowFlags_NoBringToFrontOnFocus;

}

void Canvas::draw() {
    ImGui::SetNextWindowPos(_pos_vec, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(_size_vec, ImGuiCond_FirstUseEver);
    ImGui::Begin(_window_name, &DOM::canvas_shown, _style_flag);
    ImGui::Text("TODO: Draw canvas layout.");
    ImGui::End();
}

void Canvas::onCanvasSizeChanged() {
    _pos_vec  = ImVec2(DOM::gap_left + DOM::width_panel_normal + DOM::gap_padding, DOM::gap_top + DOM::gap_padding + DOM::height_panel_normal);
    _size_vec = ImVec2(DOM::canvas_width - DOM::gap_left*2 - DOM::width_panel_normal*2 - DOM::gap_padding*2, DOM::canvas_height - DOM::gap_top*2 - DOM::gap_padding - DOM::height_panel_normal);
    ImGui::SetWindowPos(_window_name, _pos_vec, ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(_window_name, _size_vec, ImGuiCond_FirstUseEver);
}

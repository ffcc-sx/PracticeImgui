/*
 * Author  : SunXin
 * Modify  : 2022-11-19
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#include "Canvas.h"
#include "imgui_internal.h"

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
    ImGui::BeginGroup();
    auto work_rect = ImGui::GetCurrentContext()->CurrentWindow->WorkRect;
    auto work_width = work_rect.Max.x - work_rect.Min.x;
    auto work_height = work_rect.Max.y - work_rect.Min.y;
    ImGui::BeginChild("canvas_content", ImVec2(work_width, work_height), true, _style_flag);
    // Empty child with border only used to show content area.
    ImGui::EndChild();
    ImGui::EndGroup();
    // Begin render canvas content sub window.
    if (!ImGui::IsMouseDragging(0) && ImGui::BeginDragDropTarget()) {
        cout << "Drag helper dropped" << endl;
        if (ImGui::AcceptDragDropPayload("drag_helper")) {
            const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F);
            // if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
            //     memcpy((float *) &saved_palette[n], payload->Data, sizeof(float) * 4);
            ImGui::EndDragDropTarget();
        }
    }

    ImGui::End();

}

void Canvas::onCanvasSizeChanged() {
    _pos_vec  = ImVec2(DOM::gap_left + DOM::width_panel_normal + DOM::gap_padding, DOM::gap_top + DOM::gap_padding + DOM::height_panel_normal);
    _size_vec = ImVec2(DOM::canvas_width - DOM::gap_left*2 - DOM::width_panel_normal*2 - DOM::gap_padding*2, DOM::canvas_height - DOM::gap_top*2 - DOM::gap_padding - DOM::height_panel_normal);
    ImGui::SetWindowPos(_window_name, _pos_vec, ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(_window_name, _size_vec, ImGuiCond_FirstUseEver);
}

void Canvas::appendWidget() {

}

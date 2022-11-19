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
    // Empty child with border only used to show content area.
    ImGui::BeginGroup();
    auto work_rect = ImGui::GetCurrentContext()->CurrentWindow->WorkRect;
    auto work_width = work_rect.Max.x - work_rect.Min.x;
    auto work_height = work_rect.Max.y - work_rect.Min.y;
    ImGui::BeginChild("canvas_content", ImVec2(work_width, work_height), true, _style_flag);
    ImGui::EndChild();
    ImGui::EndGroup();
    // Begin render canvas content sub window.
    if (!ImGui::IsMouseDragging(0) && ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("drag_helper", ImGuiDragDropFlags_AcceptPeekOnly)) {
            auto payload_data = (const DOM::widget_info_t*)payload->Data;
            auto imgui_io = ImGui::GetIO();
            DOM::widget_info_t info(*payload_data);
            info.id = DOM::_canvas_id_serial++;
            info.pos = imgui_io.MousePos;
            cout << "new widget appended("
                << "id:" << info.id << "|"
                << "type:" << info.type << "|"
                << "position:" << info.pos.x << "|" << info.pos.y << ")" << endl;
            DOM::canvas_widgets.insert(std::make_pair(info.id, info));
            ImGui::EndDragDropTarget();
        }
    }

    // Append widgets.
    ImGuiWindowFlags widgets_flags = ImGuiWindowFlags_None;
    widgets_flags |= ImGuiWindowFlags_NoDecoration;
    widgets_flags |= ImGuiWindowFlags_NoResize;
    widgets_flags |= ImGuiWindowFlags_NoMove;
    widgets_flags |= ImGuiWindowFlags_NoSavedSettings;
    widgets_flags |= ImGuiWindowFlags_NoScrollbar;
    widgets_flags |= ImGuiWindowFlags_NoBackground;
    for(const auto & canvas_widget : DOM::canvas_widgets) {
        ImGui::SetNextWindowPos(canvas_widget.second.pos, ImGuiCond_Always, ImVec2(0.5, 0.5));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        char widget_id[32];
        sprintf(widget_id, "##%d", canvas_widget.second.id);
        ImGui::Begin(widget_id, nullptr, widgets_flags);
        cout << "New ID is:" << widget_id << endl;
        switch (canvas_widget.second.type) {
            case DOM::WidgetPushButton: {
                ImGui::Button("Button");
                break;
            }
        }
        ImGui::PopStyleVar();
        ImGui::End();
    }

    ImGui::End();
}

void Canvas::onCanvasSizeChanged() {
    _pos_vec  = ImVec2(DOM::gap_left + DOM::width_panel_normal + DOM::gap_padding, DOM::gap_top + DOM::gap_padding + DOM::height_panel_normal);
    _size_vec = ImVec2(DOM::canvas_width - DOM::gap_left*2 - DOM::width_panel_normal*2 - DOM::gap_padding*2, DOM::canvas_height - DOM::gap_top*2 - DOM::gap_padding - DOM::height_panel_normal);
    ImGui::SetWindowPos(_window_name, _pos_vec, ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(_window_name, _size_vec, ImGuiCond_FirstUseEver);
}


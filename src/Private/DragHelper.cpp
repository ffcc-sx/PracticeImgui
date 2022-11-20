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

    auto &&hold_size = ImVec2(128, 32);
    auto &&hold_pos = io.MousePos;
    if(DOM::drag_action == DOM::DragActionType::ActionAppendFromToolbox) {
        ImGui::SetNextWindowPos(hold_pos, ImGuiCond_Always, ImVec2(0.5, 0.5));
    } else if (DOM::drag_action == DOM::DragActionType::ActionMoveOnCanvas) {
        auto target = DOM::canvas_widgets.at(DOM::drag_target_id);
        DOM::drag_vec2 = ImGui::GetMouseDragDelta();
        hold_pos.x = target.pos.x + DOM::drag_vec2.x;
        hold_pos.y = target.pos.y + DOM::drag_vec2.y;
        ImGui::SetNextWindowPos(hold_pos, ImGuiCond_Always, ImVec2(0.5, 0.5));
        // TODO: Update hold size with user setting.
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (!ImGui::Begin("Holding Widget", nullptr, _style_flag))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }
    // TODO: The size of initialize should be user **or** default.
    ImGui::Button("Button", ImVec2(128, 32));

    //switch (target.type) {
    //    case DOM::WidgetPushButton: {
    //        if (ImGui::Button("Button", target.size)) {
    //            DOM::drag_shown = false;
    //        }
    //        break;
    //    }
    //}

    ImGui::PopStyleVar();
    ImGui::End();
}

void DragHelper::update() {
    // Handle state shift.
    if(_current_state != DOM::drag_shown) {
        _current_state = DOM::drag_shown;
        if(!_current_state) {
            for_each(DOM::canvas_widgets.begin(), DOM::canvas_widgets.end(),
                     [](decltype(DOM::canvas_widgets)::value_type &item) {
                if(item.second.state == 1) {
                    auto pos_mouse = ImGui::GetIO().MousePos;
                    item.second.pos.x += DOM::drag_vec2.x;
                    item.second.pos.y += DOM::drag_vec2.y;
                    cout << "Repair pos:"
                         << DOM::drag_vec2.x << "|" << DOM::drag_vec2.y << "|"
                         << item.second.pos.x << "|" << item.second.pos.y << endl;
                    if(item.second.pos.x < DOM::canvas_visible_left)    item.second.pos.x = DOM::canvas_visible_left;
                    if(item.second.pos.x > DOM::canvas_visible_right)   item.second.pos.x = DOM::canvas_visible_right;
                    if(item.second.pos.y < DOM::canvas_visible_top)     item.second.pos.y = DOM::canvas_visible_top;
                    if(item.second.pos.y > DOM::canvas_visible_bottom)  item.second.pos.y = DOM::canvas_visible_bottom;

                    // Update widget state to normal.
                    item.second.state = 0;
                    // cout << "area:"
                    //      << DOM::canvas_visible_left << "|" << DOM::canvas_visible_right << "|"
                    //      << DOM::canvas_visible_top << "|" << DOM::canvas_visible_bottom << endl;
                    // cout << "mouse:"
                    //      << pos_mouse.x << "|" << pos_mouse.y << endl;
                    // cout << "set pos:"
                    //      << item.second.pos.x << "|" << item.second.pos.y << endl;
                }
            });
        }
    }
    // Render helper.
    if(DOM::drag_shown) draw();

}



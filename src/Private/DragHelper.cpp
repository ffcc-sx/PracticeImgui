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

void DragHelper::update() {
    if(_current_state != DOM::drag_shown) {
        _current_state = DOM::drag_shown;
        if(!_current_state) {
            for_each(DOM::canvas_widgets.begin(), DOM::canvas_widgets.end(),
                     [](decltype(DOM::canvas_widgets)::value_type &item) {
                if(item.second.state == 1) {
                    auto pos_mouse = ImGui::GetIO().MousePos;
                    item.second.pos = pos_mouse;
                    if(item.second.pos.x < DOM::canvas_visible_left)    item.second.pos.x = DOM::canvas_visible_left;
                    if(item.second.pos.x > DOM::canvas_visible_right)   item.second.pos.x = DOM::canvas_visible_right;
                    if(item.second.pos.y < DOM::canvas_visible_top)     item.second.pos.y = DOM::canvas_visible_top;
                    if(item.second.pos.y > DOM::canvas_visible_bottom)  item.second.pos.y = DOM::canvas_visible_bottom;

                    item.second.state = 0;
                    cout << "area:"
                         << DOM::canvas_visible_left << "|" << DOM::canvas_visible_right << "|"
                         << DOM::canvas_visible_top << "|" << DOM::canvas_visible_bottom << endl;
                    cout << "mouse:"
                         << pos_mouse.x << "|" << pos_mouse.y << endl;
                    cout << "set pos:"
                         << item.second.pos.x << "|" << item.second.pos.y << endl;
                }
            });
        }
    }
    if(DOM::drag_shown) draw();

}



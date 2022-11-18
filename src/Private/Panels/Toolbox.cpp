/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#include "Toolbox.h"

Toolbox::Toolbox() {
    _holding_flag |= ImGuiWindowFlags_NoNav;
    _holding_flag |= ImGuiWindowFlags_NoCollapse;
    _holding_flag |= ImGuiWindowFlags_NoSavedSettings;
    _holding_flag |= ImGuiWindowFlags_NoNavInputs;
    _holding_flag |= ImGuiWindowFlags_NoNavFocus;
}

void Toolbox::draw() {
    if(!ImGui::Begin("banner_test", nullptr, _holding_flag)) {
        ImGui::End();
        return;
    }
    ImGui::Text("TODO: Draw banner.");
    ImGui::End();
}

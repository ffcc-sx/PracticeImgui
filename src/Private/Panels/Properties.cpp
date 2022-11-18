/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#include "Properties.h"

Properties::Properties() {
    _holding_flag |= ImGuiWindowFlags_NoTitleBar;
    _holding_flag |= ImGuiWindowFlags_NoScrollbar;
    _holding_flag |= ImGuiWindowFlags_NoResize;
    _holding_flag |= ImGuiWindowFlags_NoBackground;
}

void Properties::draw() {

}



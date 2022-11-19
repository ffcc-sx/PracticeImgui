/*
 * Author  : SunXin
 * Modify  : 2022-11-19
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#pragma once

#include "Common.h"
#include "Area.h"

class DragHelper : public Area {

public:
    DragHelper();
    void        draw() override;

private:
    ImGuiWindowFlags _style_flag = 0;
    const char      *_window_name   = "Canvas layout";
};

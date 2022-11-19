/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#pragma once

#include "../Common.h"
#include "../Area.h"
#include "../DOM.h"

class Properties : public Area {

public:
    Properties();

    void        draw() override;
    void        onCanvasSizeChanged() override;

private:
    ImGuiWindowFlags _style_flag = 0;
    const char      *_window_name   = "Properties toolbox";

    ImVec2          _pos_vec        {DOM::canvas_width - DOM::gap_left - DOM::gap_padding - DOM::width_panel_normal, DOM::gap_top + DOM::gap_padding + DOM::height_panel_normal};
    ImVec2          _size_vec       {DOM::canvas_width - DOM::gap_left * 2, DOM::height_panel_normal};

};


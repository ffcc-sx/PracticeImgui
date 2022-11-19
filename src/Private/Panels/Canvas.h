/*
 * Author  : SunXin
 * Modify  : 2022-11-19
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#pragma once

#include "../Common.h"
#include "../Area.h"
#include "../DOM.h"

class Canvas : public Area {

public:
    Canvas();

    void        draw() override;
    void        onCanvasSizeChanged() override;

private:
    ImGuiWindowFlags _style_flag = 0;
    const char      *_window_name   = "Canvas layout";

    ImVec2          _pos_vec        {DOM::gap_left + DOM::width_panel_normal + DOM::gap_padding, DOM::gap_top + DOM::gap_padding + DOM::height_panel_normal};
    ImVec2          _size_vec       {DOM::canvas_width - DOM::gap_left*2 - DOM::width_panel_normal*2 - DOM::gap_padding*2, DOM::canvas_height - DOM::gap_top*2 - DOM::gap_padding - DOM::height_panel_normal};

};


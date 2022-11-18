/*
 * Author  : SunXin
 * Modify  : 2022-11-19
 * Version : 1.0.0.1
 * Content :
 *   1.Optimize member type.
 */

#pragma once

#include "../Common.h"
#include "../Area.h"

class Banner : public Area {

public:
    Banner();

    void        draw() override;
    void        onCanvasSizeChanged() override;

private:
    ImGuiWindowFlags _style_flag = 0;
    const char      *_window_name   = "Canvas banner";

    static constexpr
    ImVec2          _pos_vec()      { return {DOM::gap_left, DOM::gap_top }; }
    ImVec2          _size_vec       {DOM::canvas_width - DOM::gap_left * 2, DOM::height_fixed_normal};

};

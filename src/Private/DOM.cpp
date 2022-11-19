/*
 * Author  : SunXin
 * Modify  : 2022-11-19
 * Version : 1.0.0.1
 * Content :
 *   1.Update for header 1.0.0.1.
 */

#include "DOM.h"
#include "Panels/Toolbox.h"
#include "Panels/Banner.h"
#include "Panels/Properties.h"
#include "Panels/Canvas.h"

std::vector<Area*>  DOM::windows {};
bool            DOM::demo_shown     {false};

unique_ptr<DragHelper>      DOM::drag_helper   {};
bool            DOM::drag_shown     {false};
ImVec2          DOM::drop_vec2      {0.0f, 0.0f};
DOM::widget_info_t  DOM::drag_info      {};

bool            DOM::banner_shown   {true};

float           DOM::canvas_width   {800};
float           DOM::canvas_height  {600};
bool            DOM::canvas_shown   {true};

int             DOM::_canvas_id_serial {0};
unordered_map<int, DOM::widget_info_t> DOM::canvas_widgets {};


bool DOM::initialize() {
    // Append integrated panels.
    drag_helper.reset(new DragHelper);
    windows.push_back(new Banner);
    windows.push_back(new Toolbox);
    windows.push_back(new Properties);
    windows.push_back(new Canvas);
    return true;
}
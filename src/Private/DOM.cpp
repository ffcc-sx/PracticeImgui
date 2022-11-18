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

float           DOM::canvas_width   {800};
float           DOM::canvas_height  {600};
bool            DOM::canvas_shown   {true};

bool DOM::initialize() {
    windows.push_back(new Banner);
    windows.push_back(new Toolbox);
    windows.push_back(new Properties);
    windows.push_back(new Canvas);
    return true;
}

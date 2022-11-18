/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#include "DOM.h"
#include "Panels/Toolbox.h"
#include "Panels/Banner.h"
#include "Panels/Properties.h"

std::vector<Area*>  DOM::windows {};

int          DOM::canvas_width  {800};
int          DOM::canvas_height {600};

bool DOM::initialize() {
    windows.push_back(new Banner);
    windows.push_back(new Toolbox);
    windows.push_back(new Properties);
    return true;
}

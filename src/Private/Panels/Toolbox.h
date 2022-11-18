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

class Toolbox : public Area {

public:
    Toolbox();

    void        draw() override;

private:
    ImGuiWindowFlags _holding_flag = 0;

};

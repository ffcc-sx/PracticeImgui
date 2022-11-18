/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#pragma once

#include "Common.h"
#include "DOM.h"

class Area {

public:
    /// \brief To overwrite for rending defines.
    virtual void        draw() = 0;

};


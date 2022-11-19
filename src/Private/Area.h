/*
 * Author  : SunXin
 * Modify  : 2022-11-19
 * Version : 1.0.0.1
 * Content :
 *   1.Extend onCanvasSizeChanged() interface.
 */

#pragma once

#include "Common.h"

class Area {

public:
    /// \brief To overwrite for rending defines.
    virtual void        draw() = 0;
    /// \brief The work area size changed handler, nop by default.
    virtual void        onCanvasSizeChanged() {};
};


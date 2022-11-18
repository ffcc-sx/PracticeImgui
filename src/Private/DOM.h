/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#pragma once

#include "Common.h"

class Area;
/// \brief Static instance for view status and data storage.
class DOM {

public:
    static bool    initialize();
    void    loadCommonConfigure()   { }
    void    loadProjectConfig()     { }

    static std::vector<Area*>      windows;

    static int          canvas_width;
    static int          canvas_height;



    bool debug_shown = true;

    bool banner_show = true;

    bool properties_show = true;

};


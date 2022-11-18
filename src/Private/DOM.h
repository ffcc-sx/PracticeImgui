/*
 * Author  : SunXin
 * Modify  : 2022-11-19
 * Version : 1.0.0.1
 * Content :
 *   1.Extend 3 const float value;
 *   2.Append magic number translator;
 *   3.Optimize value type from int to float.
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

    inline static int   getInt32(float x) {
        uint32_t n = ((*(uint32_t *) &x) & 0x80000000) ? 0xFFC00000 : 0;
        x += 12582912.0f;
        return (int32_t) (((*(uint32_t *) &x) & 0x3FFFFF) | n);
    }
    static inline int   getInt32(double x) {
        x += 6755399441055744.0;
        return *(int32_t *) &x;
    }

    // ==================== Constant defines ==================== //
    constexpr static const float    height_fixed_normal    = 64.0f;
    constexpr static const float    gap_left        = 10.0f;
    constexpr static const float    gap_top         = 10.0f;

    static std::vector<Area*>      windows;

    static float          canvas_width;
    static float          canvas_height;

    bool debug_shown = true;

    // NoUsed
    bool banner_show = true;

    bool properties_show = true;

};


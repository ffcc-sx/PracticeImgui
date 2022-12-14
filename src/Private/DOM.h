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
#include "DragHelper.h"
#include "Area.h"

using namespace std;

/// \brief Static instance for view status and data storage.
class DOM {

public:
    enum DragType {
        WidgetUnknown,
        WidgetPushButton,
    };
    struct widget_info_t {
        widget_info_t() = default;
        widget_info_t(const widget_info_t &inst) {
            id   = inst.id;
            type = inst.type;
            size = inst.size;
            pos  = inst.pos;
            state= inst.state;
        };
        widget_info_t &operator=(const widget_info_t &inst) {
            this->id   = inst.id;
            this->type = inst.type;
            this->size = inst.size;
            this->pos  = inst.pos;
            this->state= inst.state;
            return *this;
        };

        int         id      {};
        int         type    {WidgetUnknown};
        ImVec2      size    {};
        ImVec2      pos     {};
        // 0:Normal; 1:Moving; 2:Appending;
        int         state   {};
    };

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

    // ==================== Global status       ====================//
    static std::vector<Area*>      windows;
    static bool         demo_shown;

    // ==================== Canvas status       ====================//
    static bool             canvas_shown;
    static float            canvas_width;
    static float            canvas_height;
    static float            canvas_visible_left;
    static float            canvas_visible_top;
    static float            canvas_visible_right;
    static float            canvas_visible_bottom;
    static float            canvas_valid_left;
    static float            canvas_valid_top;
    static float            canvas_valid_right;
    static float            canvas_valid_bottom;

    static unordered_map<int, widget_info_t> canvas_widgets;
    static int              _canvas_id_serial;

    // ==================== Drag helper         ====================//
    enum class DragActionType { ActionNone, ActionAppendFromToolbox, ActionMoveOnCanvas };
    static unique_ptr<DragHelper>   drag_helper;
    static DragActionType   drag_action;
    static int              drag_target_id;
    static bool             drag_shown;
    static ImVec2           drag_vec2;
    static widget_info_t    drag_info;

    // ==================== Banner status       ====================//
    static bool             banner_shown;

    // ==================== Constant defines    ====================//
    constexpr static const float    width_panel_normal  = 256.0f;
    constexpr static const float    height_panel_normal = 64.0f;
    constexpr static const float    gap_left            = 10.0f;
    constexpr static const float    gap_top             = 10.0f;
    constexpr static const float    gap_padding         = 5.0f;

    bool properties_show = true;
};


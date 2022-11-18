/*
 * Author  : SunXin
 * Modify  : 2022-11-16
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Headers.h"

#ifdef __cplusplus
extern "C" {
#endif

void resizeCanvas();

class Looper {
public:
    static Looper* instance() { if(!_instance) _instance = new Looper; return _instance; }
    bool initialize();
    void start();

    [[nodiscard]] static GLFWwindow*    window()    { return _instance->_window; }
    [[nodiscard]] static int            width()     { return _instance->_width; }
    [[nodiscard]] static int            height()    { return _instance->_height; }

private:
    Looper() = default;
    ~Looper();

    GLFWwindow       *_window;
    int              _width;
    int              _height;
    ImVec4           *_color;

    static inline void      _loop_process();
    void                    _loop_body();
    static Looper           *_instance;

    bool _init_gl();
    bool _init_imgui();

#ifdef __EMSCRIPTEN__
private:
    void _onCanvasSizeChanged();

#endif // def __EMSCRIPTEN__
};

#ifdef __cplusplus
}
#endif
/*
 * Author  : SunXin
 * Modify  : 2022-11-16
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#pragma once

#include "Common.h"

#ifdef __cplusplus
extern "C" {
#endif

class Looper {
public:
    /// \brief Singleton referencer.
    static Looper* instance() { if(!_instance) _instance = new Looper; return _instance; }
    /// \brief Initialize looper.
    bool initialize();
    /// \brief Start main looper for edit or data refresh.
    static void start();

private:
    /// \brief Forbidden with singleton.
    Looper();
    /// \brief Forbidden with singleton.
    ~Looper();

    /// \brief Export static function pointer to imgui and avoid heads importing with main.
    static inline void      _loop_process();
    /// \brief Rendering process function.
    void                    _loop_body();
    /// \brief Initializer for GLFW, must invoke before imgui for demo reason.
    bool                    _init_gl();
    /// \brief Initializer for ImGui module.
    bool                    _init_imgui();

    bool            _sign_initialized;  //-< Guarantee GLFW and ImGui initialized before start().
    GLFWwindow      *_window;           //-< GLFW window instance.
    ImVec4          _color;             //-< Background color of canvas configure.
    static Looper   *_instance;         //-< For singleton looper class.

#ifdef __EMSCRIPTEN__
private:
    /// \brief Synchronize with front-end canvas.
    void _onCanvasSizeChanged();
#endif // def __EMSCRIPTEN__
};

#ifdef __cplusplus
}
#endif
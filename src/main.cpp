/*
 * Author  : SunXin
 * Modify  : 2022-11-17
 * Version : 1.0.0.1
 * Content :
 *   1.Move main loop logic to Looper class.
 */

#include <stdio.h>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Private/Looper.h"

extern "C" int main(int argc, char** argv) {
    if(!Looper::instance()->initialize()) {
        std::cout << "[IMGUI] Engine initialize failed." << std::endl;
        return 1;
    } else {
        // Mark: this method will block thread.
        Looper::instance()->start();
    }

    std::cout << "Main loop of UI thread has been broken." << std::endl;
    return 0;
}

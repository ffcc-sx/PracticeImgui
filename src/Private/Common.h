/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.1
 * Content :
 *   1.Append ImGui heads needed.
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

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

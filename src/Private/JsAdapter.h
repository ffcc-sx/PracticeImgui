/*
 * Author  : SunXin
 * Modify  : 2022-11-17
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#pragma once
#ifdef __EMSCRIPTEN__

extern "C" int canvas_get_width();
extern "C" int canvas_get_height();

#endif // def __EMSCRIPTEN__

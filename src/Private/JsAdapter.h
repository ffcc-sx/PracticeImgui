/*
 * Author  : SunXin
 * Modify  : 2022-11-17
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#pragma once
#ifdef __EMSCRIPTEN__

/// \brief Retrieve front-end canvas width size.
extern "C" int canvas_get_width();
/// \brief Retrieve front-end canvas height size.
extern "C" int canvas_get_height();
/// \brief Notice front-end to resize canvas size.
extern "C" void resizeCanvas();

#endif // def __EMSCRIPTEN__

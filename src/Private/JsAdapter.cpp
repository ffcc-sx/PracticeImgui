/*
 * Author  : SunXin
 * Modify  : 2022-11-17
 * Version : 1.0.0.1
 * Content :
 *   1.Enable function when EMSCRIPTEN imported.
 */

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

EM_JS(int, canvas_get_width, (), {
    return Module.canvas.width;
});

EM_JS(int, canvas_get_height, (), {
    return Module.canvas.height;
});

EM_JS(void, resizeCanvas, (), {
    js_resizeCanvas();
});

#endif
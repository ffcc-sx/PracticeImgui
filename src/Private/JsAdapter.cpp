//
// Created by sunny on 2022-11-17.
//

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif


EM_JS(int, canvas_get_width, (), {
return Module.canvas.width;
});

EM_JS(int, canvas_get_height, (), {
return Module.canvas.height;
});

EM_JS(void, resizeCanvas, (), {
js_resizeCanvas();
});

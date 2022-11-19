/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.1
 * Content :
 *   1.Notify tool panel when canvas size changed.
 */

#include "Looper.h"
#include "JsAdapter.h"
#include "DOM.h"

using namespace std;
Looper   *Looper::_instance = nullptr;

Looper::Looper()
: _color(0.45f, 0.55f, 0.60f, 1.00f)
, _sign_initialized(false)
, _window(nullptr) { }

Looper::~Looper() {
    glfwTerminate();
}

void Looper::_loop_process() {
    Looper::instance()->_loop_body();
}

void Looper::_loop_body() {
#ifdef __EMSCRIPTEN__
    int canvas_width    = canvas_get_width();
    int canvas_height   = canvas_get_height();
    if (canvas_width != DOM::canvas_width || canvas_height != DOM::canvas_height) {
        DOM::canvas_width = canvas_width;
        DOM::canvas_height = canvas_height;
        _onCanvasSizeChanged();
    }
#endif // def __EMSCRIPTEN__
    // Begin render process.
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags holding_flag1 = 0;
    holding_flag1 |= ImGuiWindowFlags_NoTitleBar;
    holding_flag1 |= ImGuiWindowFlags_NoScrollbar;
    holding_flag1 |= ImGuiWindowFlags_NoResize;
    holding_flag1 |= ImGuiWindowFlags_NoBackground;

    // TODO: Need a DOM to buffer status of widgets.
    for_each(DOM::windows.begin(),
             DOM::windows.end(),
             [=](Area* item) {
        item->draw();
    });

    DOM::drag_helper->update();

    if(DOM::demo_shown) {
        ImGui::SetNextWindowPos(ImVec2(50, 20), ImGuiCond_FirstUseEver);
        ImGui::ShowDemoWindow(&DOM::demo_shown);
    }

    ImGui::Render();

    int display_w, display_h;
    glfwMakeContextCurrent(_window);
    glfwGetFramebufferSize(_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(_color.x, _color.y, _color.z, _color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwMakeContextCurrent(_window);
}

void Looper::start() {
    // Member _window must be initialized after init().
    emscripten_set_main_loop(Looper::_loop_process, 0, 1);
}

bool Looper::_init_gl() {
    if( !glfwInit() ) {
        std::cout << "[Looper] Failed to initialize GLFW" << std::endl;
        return false;
    }

    // 4x antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context

    _window = glfwCreateWindow( 800, 600, "ETest UI[Widget] Debugger", nullptr, nullptr);
    if( _window == nullptr ) {
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return false;
    }
    // Initialize GLEW
    glfwMakeContextCurrent(_window);
    return true;
}

bool Looper::_init_imgui() {
    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    IM_ASSERT(_window);
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init();

    // Setup style
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();

    // Load Fonts
    // io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 23.0f);
    // io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 18.0f);
    // io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 26.0f);
    // io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 32.0f);
    // io.Fonts->AddFontDefault();

    resizeCanvas();

    return true;
}

bool Looper::initialize() {
    if(_sign_initialized) return true;
    _sign_initialized = true;
    _sign_initialized &= _init_gl();
    _sign_initialized &= _init_imgui();
    _sign_initialized &= DOM::initialize();
    return _sign_initialized;
}

#ifdef __EMSCRIPTEN__

void Looper::_onCanvasSizeChanged() {
    glfwSetWindowSize(_window, DOM::getInt32(DOM::canvas_width), DOM::getInt32(DOM::canvas_height));
    ImGui::SetCurrentContext(ImGui::GetCurrentContext());
    for_each(DOM::windows.begin(), DOM::windows.end(), [](Area* item) {
        item->onCanvasSizeChanged();
    });
}

#endif // def __EMSCRIPTEN__


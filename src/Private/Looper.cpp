/*
 * Author  : SunXin
 * Modify  : 2022-11-16
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#include "Looper.h"

Looper   *Looper::_instance = nullptr;

Looper::~Looper() {
    glfwTerminate();
}

void Looper::_loop_process() {
    Looper::instance()->_loop_body();
}

void Looper::_loop_body() {

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

    _color = new ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Open a window and create its OpenGL context
    _width = _height = 300;
    _window = glfwCreateWindow( _width, _height, "ETest UI[Widget] Debugger", nullptr, nullptr);
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
    auto sign_succeed = true;
    sign_succeed &= _init_gl();
    sign_succeed &= _init_imgui();
    return sign_succeed;
}



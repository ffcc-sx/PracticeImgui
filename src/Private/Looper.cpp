/*
 * Author  : SunXin
 * Modify  : 2022-11-18
 * Version : 1.0.0.1
 * Content :
 *   1.Notify tool panel when canvas size changed.
 */

#include "Looper.h"
#include "JsAdapter.h"
#include "Area.h"

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

    static bool sign_closed_holding = false;
    static bool sign_origin_shown = true;
    // 1. Show a simple window.
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
    {
        static float f = 0.0f;
        static int counter = 0;
        ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
        // ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        // ImGui::ColorEdit3("clear color", (float*)&_color); // Edit 3 floats representing a color

        // ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
        // ImGui::Checkbox("Another Window", &show_another_window);

        if (sign_origin_shown) {
            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0)) {
                ImGui::Text("Drag begin");
                // Show the holding widget.
                sign_closed_holding = true;
                sign_origin_shown = false;
            }
        }

        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    ImGuiWindowFlags holding_flag = 0;
    holding_flag |= ImGuiWindowFlags_NoTitleBar;
    holding_flag |= ImGuiWindowFlags_NoScrollbar;
    holding_flag |= ImGuiWindowFlags_NoResize;
    holding_flag |= ImGuiWindowFlags_NoBackground;
    if (sign_closed_holding) {
        auto io = ImGui::GetIO();
        ImGui::SetNextWindowPos(io.MousePos, ImGuiCond_Always, ImVec2(0.5, 0.5));
        if (!ImGui::Begin("Holding Widget", &sign_closed_holding, holding_flag))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }
        if (ImGui::Button("Close Me")) {
            sign_closed_holding = false;
            sign_origin_shown = true;
        }
        ImGui::End();
    }

    static bool show_demo_window = true;
    // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway.
    // Here we just want to make the demo initial state a bit more friendly!
    ImGui::SetNextWindowPos(ImVec2(50, 20), ImGuiCond_FirstUseEver);
    ImGui::ShowDemoWindow(&show_demo_window);

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


/*
 * Author  : SunXin
 * Modify  : 2022-11-16
 * Version : 1.0.0.0
 * Content :
 *   1.First initialize.
 */

#include "Looper.h"
#include "JsAdapter.h"

Looper   *Looper::_instance = nullptr;

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
    if (canvas_width != _width || canvas_height != _height) {
        _width = canvas_width;
        _height = canvas_height;
        _onCanvasSizeChanged();
    }
#endif // def __EMSCRIPTEN__

    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

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
    glClearColor(_color->x, _color->y, _color->z, _color->w);
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

    _color = new ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Open a window and create its OpenGL context
    _width  = 800;
    _height = 600;
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
    auto sign_succeed = true;
    sign_succeed &= _init_gl();
    sign_succeed &= _init_imgui();
    return sign_succeed;
}

#ifdef __EMSCRIPTEN__

void Looper::_onCanvasSizeChanged() {
    glfwSetWindowSize(_window, _width, _height);
    ImGui::SetCurrentContext(ImGui::GetCurrentContext());
}

#endif // def __EMSCRIPTEN__


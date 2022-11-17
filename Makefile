CXX = emcc
OUTPUT = publish\\UiCanvas.js
IMGUI_DIR:=library/imgui

SOURCES = src/main.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_widgets.cpp $(IMGUI_DIR)/imgui_tables.cpp

LIBS = -lGL
WEBGL_VER = -s USE_WEBGL2=1 -s USE_GLFW=3 -s FULL_ES3=1
#WEBGL_VER = USE_GLFW=2
USE_WASM = -s WASM=1

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(SOURCES)
	mkdir -p publish
	$(CXX)  $(SOURCES) -std=c++11 -o $(OUTPUT) $(LIBS) $(WEBGL_VER) -O2 --preload-file resources/fonts $(USE_WASM) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

clean:
	rm -f $(OUTPUT)

# Author  : SunXin
# Modify  : 2022-11-16
# Version : 1.0.0.0
# Content :
#   1.First initialize.

CXX = emcc
OUTPUT = publish/UiCanvas.js
IMGUI_DIR:=library/imgui
INCLUDES := library

SOURCES := src/main.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp
SOURCES += $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/imgui_tables.cpp

SOURCES += src/Private/Looper.cpp
SOURCES += src/Private/JsAdapter.cpp

LIBS = -lGL
WEBGL_VER = -s USE_WEBGL2=1 -s USE_GLFW=3 -s FULL_ES3=1
#WEBGL_VER = USE_GLFW=2
USE_WASM = -s WASM=1

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CXX)  $(SOURCES) -std=c++11 -o $(OUTPUT) $(LIBS) $(WEBGL_VER) -O2 --preload-file resources/fonts $(USE_WASM) -I$(INCLUDES) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

clean:
	rm -f $(OUTPUT)

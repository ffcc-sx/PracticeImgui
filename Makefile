# Author  : SunXin
# Modify  : 2022-11-16
# Version : 1.0.0.0
# Content :
#   1.First initialize.


ifeq ($(OS), Windows_NT)
	CXX = emcc.bat
else
	CXX = emcc
endif
OUTPUT = publish/UiCanvas.js
IMGUI_DIR:=library/imgui
HEADS += -Ilibrary -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

SOURCES := src/main.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SOURCES += $(wildcard $(IMGUI_DIR)/*.cpp)
SOURCES += $(wildcard src/Private/*.cpp)
SOURCES += $(wildcard src/Private/Panels/*.cpp)

LIBS = -lGL

FLAGS := -s USE_WEBGL2=1 -s USE_GLFW=3 -s FULL_ES3=1
#WEBGL_VER = USE_GLFW=2
FLAGS += -s WASM=1
FLAGS += -std=c++11
FLAGS += --preload-file resources/fonts


all: $(SOURCES) $(OUTPUT)

.PHONY: $(OUTPUT)
$(OUTPUT): $(SOURCES)
	$(CXX) $(FLAGS) -o $(OUTPUT) $(SOURCES) $(LIBS) $(HEADS)

.PHONY: clean
clean:
	rm -f $(OUTPUT)

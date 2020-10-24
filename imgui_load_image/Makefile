#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need SDL2 (http://www.libsdl.org):
# Linux:
#   apt-get install libsdl2-dev
# Mac OS X:
#   brew install sdl2
# MSYS2:
#   pacman -S mingw-w64-i686-SDL2
#

#CXX = g++
#CXX = clang++

EXE = imgui_loader
SOURCES = main.cpp dmgui.cpp
#SOURCES += ../../libraries_cpp/ImGuiFileDialog/ImGuiFileDialog.cpp
SOURCES += ../../libraries_cpp/dear_imgui/examples/imgui_impl_sdl.cpp ../../libraries_cpp/dear_imgui/examples/imgui_impl_opengl2.cpp
SOURCES += ../../libraries_cpp/dear_imgui/imgui.cpp ../../libraries_cpp/dear_imgui/imgui_demo.cpp ../../libraries_cpp/dear_imgui/imgui_draw.cpp ../../libraries_cpp/dear_imgui/imgui_widgets.cpp ../../libraries_cpp/IMGuiFileDialog/ImGuiFileDialog.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

CXXFLAGS = -I../../libraries_cpp/dear_imgui/examples/ -I../../libraries_cpp/dear_imgui/ -I../../libraries_cpp/ImGuiFileDialog/ -I.
# -I../../libraries_cpp/sdl2/include/ -I.
CXXFLAGS += -g -std=c++17 -Wall -Wformat 
LIBS =

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += -lSDL2_image -lGL -ldl `sdl2-config --libs` 

	CXXFLAGS += `sdl2-config --cflags`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo `sdl2-config --libs`
	LIBS += -L/usr/local/lib -L/opt/local/lib

	CXXFLAGS += `sdl2-config --cflags`
	CXXFLAGS += -I/usr/local/include -I/opt/local/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	ECHO_MESSAGE = "MinGW"
	LIBS += -lgdi32 -lopengl32 -limm32 `pkg-config --static --libs sdl2 -lSDL2_image`

	CXXFLAGS += `pkg-config --cflags sdl2`
	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

#%.o:../%.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<

#%.o:../../%.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:../../libraries_cpp/dear_imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:../../libraries_cpp/dear_imgui/examples/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:../../libraries_cpp/ImGuiFileDialog/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)

objclean:
	rm -f $(OBJS)

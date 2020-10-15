@REM Build for Visual Studio compiler. Run your copy of vcvars32.bat or vcvarsall.bat to setup command-line compiler.
set OUT_DIR=Debug
set OUT_EXE=baseImgui_exe
set INCLUDES=/I..\..\libraries\dear_imgui\examples /I..\..\libraries\dear_imgui /I..\..\libraries\sdl2\include
set SOURCES=main.cpp ..\..\libraries\dear_imgui\examples\imgui_impl_sdl.cpp ..\..\libraries\dear_imgui\examples\imgui_impl_opengl2.cpp ..\..\libraries\dear_imgui\imgui*.cpp
set LIBS=/libpath:..\..\libraries\sdl2\lib\x86 SDL2.lib SDL2main.lib opengl32.lib
mkdir %OUT_DIR%
cl /nologo /Zi /MD %INCLUDES% %SOURCES% /Fe%OUT_DIR%/%OUT_EXE%.exe /Fo%OUT_DIR%/ /link %LIBS% /subsystem:console

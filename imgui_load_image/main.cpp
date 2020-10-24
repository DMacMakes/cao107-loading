// dear imgui: standalone example application for SDL2 + OpenGL
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
#include "imgui.h"
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif  
#include <iostream>
#include <string>
#include <vector>;
#include <assert.h>
#include "imgui_internal.h"
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "ImGuiFileDialog.h"
#include "CImg.h"
//#include "SDL_image.h" 
#include <SDL_image.h>
#include "dmgui.h";
using cimg_library::cimg::nearest_pow2;

// Global variables to allow access to the window and gL_context from create and destroy funcs 
SDL_Window* window = nullptr; 
// = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
SDL_GLContext gl_context;
// = SDL_GL_CreateContext(window);

void Init_SDL_OpenGL();
void Destroy_SDL_OpenGL();
void Render_Imgui(ImVec4&, ImGuiIO&);
void Show_Demo_Window(bool&, ImVec4&);
void Show_Load_Window(bool& show_load, bool& show_demo, bool& done, std::string image_error, int initted);
// Main code

int main(int, char**)
{
    Init_SDL_OpenGL();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    // Initialise SDL image loader
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    
    // Here's how you load an image from disk into a texture that will work with ImGui::ImGui()
    // Specifically, the DmGui::ImageTexture structure has texture_id, width and height. Explore it.
    DmGui::ImageTexture image_texture;
    image_texture.error = DmGui::Load_Image_To_GLuint_Texture(std::string("image1.png"), image_texture);

    bool show_demo_window = false;
    bool show_load_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
      // Poll and handle events (inputs, window resize, etc.) In particular, window close.
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
          done = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
          done = true;
      }

      // Start the Dear ImGui frame - as in frames per second, not window-frame
      ImGui_ImplOpenGL2_NewFrame();
      ImGui_ImplSDL2_NewFrame(window);
      ImGui::NewFrame();

      // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
      if (show_demo_window)
      {
        Show_Demo_Window(show_demo_window, clear_color);
      }

      //2. Show CAO107 media loader window, the core of our assessment.  
      if (show_load_window)
      {
        Show_Load_Window(show_load_window, show_demo_window, done, image_texture.error, initted);
      }

      //3. Show each loaded image in its own window.

      // So far we've just been telling imgui what to paint on screen.
      // Now we ask it to paint it all to the screen at once (one screen draw per frame)
      Render_Imgui(clear_color, io);
    }

    // Clean up all the SDL and OpenGL stuff in memory
    Destroy_SDL_OpenGL();

    return 0;
}

void Show_Loader_Menu_Bar(bool& done)
{
  static bool show_load_message = false;
  static bool path_was_chosen = false;
  static std::string path = "";
  static std::string pathName = "";
  static std::string fileName = "";
  if (ImGui::BeginMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Load images.."))
      {
        igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseImageDlgKey", "Choose image", ".cpp,.c,.h", ".");
        // For real, display the file browser (get library).
        show_load_message = true;// Display the file browser
      }
      if (ImGui::MenuItem("Load sounds..")) // Do things if clicked;
      {
        igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseSoundDlgKey", "Choose sound", ".cpp,.c,.h", ".");
        show_load_message = true;// Display the file browser
      }
      if (ImGui::MenuItem("Quit"))
      {
        done = true;
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
      ImGui::MenuItem("Help yoself");
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  // Display file browser
    if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseImageDlgKey"))
    {
      // action if OK
      if (igfd::ImGuiFileDialog::Instance()->IsOk == true)
      {
        pathName = igfd::ImGuiFileDialog::Instance()->GetFilePathName();
        path = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();
        fileName = igfd::ImGuiFileDialog::Instance()->GetCurrentFileName();
        // action
        path_was_chosen = true;
    
      }
      // close
      igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseImageDlgKey");
    }

    if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseSoundDlgKey"))
    {
      // action if OK
      if (igfd::ImGuiFileDialog::Instance()->IsOk == true)
      {
        pathName = igfd::ImGuiFileDialog::Instance()->GetFilePathName();
        path = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();
        fileName = igfd::ImGuiFileDialog::Instance()->GetCurrentFileName();
        // action
        path_was_chosen = true;
      }
      // close
      igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseSoundDlgKey");
    }
    ImGui::Text("dear imgui (%s)", IMGUI_VERSION);
    if (show_load_message)
    {
      ImGui::Text("File browser requested..");
    }
    if (path_was_chosen)
    {
      ImGui::Text("Path %s: ", path.c_str());
      ImGui::Text("PathName %s: ", pathName.c_str());
      ImGui::Text("CurrentFile %s: ", fileName.c_str());
    }
  }
  ImGui::Spacing();
}

void Show_Load_Window(bool& show_load, bool& show_demo, bool& done, std::string image_error, int initted)
{
  ImGuiWindowFlags window_flags = 0;
 // if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
//  if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
  window_flags |= ImGuiWindowFlags_MenuBar;
//  if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
  // window_flags |= ImGuiWindowFlags_NoResize;
  //  if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
//  if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
//  if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
//  if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
//  if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
//  if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

  ImGui::Begin("Media Loader 2020.0.1", nullptr, window_flags);
  Show_Loader_Menu_Bar(done);

  ImGui::Text("sdl image initted %d", initted);
  ImGui::Text("Image error %s", image_error.c_str());
  //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
  if (ImGui::Button("Show Demo Window")) show_demo = true;
    //show_load = false;

  ImGui::End();
}

// Shows a window the IMGui devs have created as a demo of (all? most of?) the features imgui offers.
void Show_Demo_Window(bool& show_demo, ImVec4& clear_color)
{
  ImGui::ShowDemoWindow(&show_demo);
  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo);      // Edit bools storing our window open/close state

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
  }
}

// Initialise the SDL and openGL libraries to 
// a) define and control our gui elements and
// b) create the openGL context that renders them
void Init_SDL_OpenGL()
{
  // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
  {
    printf("Error: %s\n", SDL_GetError());
    return;
    //return -1;
  }

  // Setup window
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
  gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1); // Enable vsync
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
  //io.ConfigViewportsNoAutoMerge = true;
  //io.ConfigViewportsNoTaskBarIcon = true;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform/Renderer bindings
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL2_Init();

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'docs/FONTS.md' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
  //io.Fonts->AddFontDefault();
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
  //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
  //IM_ASSERT(font != NULL);

}

void Render_Imgui(ImVec4& clear_color, ImGuiIO& io)
{
  // Rendering
  ImGui::Render();
  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
  ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

  // Update and Render additional Platform Windows
  // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
  //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
  }

  SDL_GL_SwapWindow(window);
}

void Destroy_SDL_OpenGL()
{
  // Cleanup
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

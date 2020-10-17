// dear imgui: standalone example application for SDL2 + OpenGL
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the example_sdl_opengl3/ folder**
// See imgui_impl_sdl.cpp for details.

#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

SDL_Window* window = nullptr;// = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
SDL_GLContext gl_context;// = SDL_GL_CreateContext(window);

void Init_SDL_OpenGL();
void Destroy_SDL_OpenGL();
void Render_Imgui(ImVec4&, ImGuiIO&);
void Show_Another_Window(bool& show);
void Show_Demo_Window(bool&, bool&, ImVec4&);
void Show_Load_Window(bool& show_load);
static void ShowExampleMenuFile();

// Main code
int main(int, char**)
{
    Init_SDL_OpenGL();
    
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    // State of interface (what's showing)
    bool show_demo_window = true;
    bool show_another_window = true;
    bool show_load_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
      // Poll and handle events (inputs, window resize, etc.)
      // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
      // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
      // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
      // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
          done = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
          done = true;
      }

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL2_NewFrame();
      ImGui_ImplSDL2_NewFrame(window);
      ImGui::NewFrame();

      // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
      if (show_demo_window)
      {
        Show_Demo_Window(show_demo_window, show_another_window, clear_color);
      }

      //2. Show CAO107 window 1. 
      if (show_load_window)
      {
        Show_Load_Window(show_load_window);
      }

      //3. Show another simple window.        
//      if (show_another_window)
//      {
//        Show_Another_Window(show_another_window);
//      }

      Render_Imgui(clear_color, io);
    }

    Destroy_SDL_OpenGL();

    return 0;
}

void Show_Loader_Menu_Bar()
{
  static bool show_load_message = false;

  if (ImGui::BeginMenuBar())
  {
    if (ImGui::BeginMenu("Menu"))
    {
      if (ImGui::MenuItem("Load Image files.."))
      {
        igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", ".");
        // For real, display the file browser (get library).
        show_load_message = true;// Display the file browser
      }
      ImGui::MenuItem("Load Audio files..", "Ctrl+a");
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Examples"))
    {
      ImGui::MenuItem("Main menu bar");
      ImGui::MenuItem("Console");
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
    // Todo: add ImGuiFileDialog files to project/library
    // See main.cpp in ImGuiFileDialog-master in cao107_y/etc/library_downloads
    if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
    {
      // action if OK
      if (igfd::ImGuiFileDialog::Instance()->IsOk == true)
      {
        std::string filePathName = igfd::ImGuiFileDialog::Instance()->GetFilePathName();
        std::string filePath = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();
        // action
      }
      // close
      igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
    }
  }
  // Display file browser
  if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
  {
    // action if OK
    if (igfd::ImGuiFileDialog::Instance()->IsOk == true)
    {
      std::string filePathName = igfd::ImGuiFileDialog::Instance()->GetFilePathName();
      std::string filePath = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();
      // action
    }
    // close
    igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
  }
  ImGui::Text("dear imgui (%s)", IMGUI_VERSION);
  if (show_load_message)
  {
    ImGui::Text("File browser requested..");
  }
  //else
 // {
  //  ImGui::Text("dear imgui says hello. (%s)", IMGUI_VERSION);
 // }
  ImGui::Spacing();
}

void Show_Load_Window(bool& show_load)
{
  ImGuiWindowFlags window_flags = 0;
 // if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
//  if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
  window_flags |= ImGuiWindowFlags_MenuBar;
//  if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
 // if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
//  if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
//  if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
//  if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
//  if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
//  if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
//  if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

  ImGui::Begin("Media Loader 2020.0.1", nullptr, window_flags);
  Show_Loader_Menu_Bar();

  //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
  if (ImGui::Button("Close Me"))
    show_load = false;
  ImGui::End();
}

// Shows a window the IMGui devs have created as a demo of (all? most of?) the features imgui offers.
void Show_Demo_Window(bool& show_demo, bool& show_another, ImVec4& clear_color)
{
  ImGui::ShowDemoWindow(&show_demo);
  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another);

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

void Show_Another_Window(bool& show)
{
  ImGui::Begin("Another Window", &show);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
  ImGui::Text("Hello from another window!");
  if (ImGui::Button("Close Me"))
    show = false;
  ImGui::End();
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

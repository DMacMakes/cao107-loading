///////////////////////////////////////////////////////////////
//  -------------
//  dmgui.h
//  -------------
//  Helper functions and bits for the CAO107 imgui + SDL2
//  setup for weeks 5-8.
//
///////////////////////////////////////////////////////////////

#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>



namespace DmGui 
{
  struct ImageTexture
  {
    GLuint texture_id{0};
    int width{0};
    int height{0};
    std::string error;
    bool isVisible {true};
  };

  std::string Load_Image_To_GLuint_Texture(std::string path, DmGui::ImageTexture& image_texture);
}

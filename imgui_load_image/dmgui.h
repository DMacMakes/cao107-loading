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
  
  // Takes a path to an image and (a reference to) and loads it using SDL2_image.
  // It converts the result to an Open GL 2D texture and puts the id etc into
  // the DmGui ImageTexture you supply. 
  std::string Load_Image_To_GLuint_Texture(std::string path, DmGui::ImageTexture& image_texture);
}

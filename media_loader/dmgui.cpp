#include "dmgui.h"
#include <SDL_image.h>
#include <string>
#include "CImg.h"
using cimg_library::cimg::nearest_pow2;

namespace DmGui
{
  std::string Load_Image_To_GLuint_Texture(std::string path, DmGui::ImageTexture& image_texture) // int& width, int& height)
  {
    SDL_Surface* image = nullptr;
    image = IMG_Load(path.c_str());
    std::string image_error = "none";
    if (!image) {
      image_error = IMG_GetError();
    }
    image_texture.width = image->w;
    image_texture.height = image->h;
    //image_error = "width: " + std::to_string(image_texture.width) + "height: " + std::to_string(image_texture.height);


    // http://forums.libsdl.org/viewtopic.php?t=8166 //////// SDL Surface TO GL Texture
    /* OpenGL pixel format for destination surface. */
    int bpp;
    Uint32 Rmask, Gmask, Bmask, Amask;
    SDL_PixelFormatEnumToMasks(SDL_PIXELFORMAT_ABGR8888, &bpp, &Rmask,
      &Gmask, &Bmask, &Amask);

    /* Create surface that will hold pixels passed into OpenGL. */
    SDL_Surface* img_rgba8888 = SDL_CreateRGBSurface(0, image_texture.width, image_texture.height, bpp,
      Rmask, Gmask, Bmask, Amask);

    /*
     * Disable blending for source surface. If this is not done, all
     * destination surface pixels end up with crazy alpha values.
     */
    SDL_SetSurfaceAlphaMod(image, 0xFF);
    SDL_SetSurfaceBlendMode(image, SDL_BLENDMODE_NONE);

    /* Blit to this surface, effectively converting the format. */
    SDL_BlitSurface(image, NULL, img_rgba8888, NULL);

    // Adding bits from
    // https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#Example-for-OpenGL-users
    /*
     * Create a blank texture with power-of-two dimensions. Then load
     * converted image data into its lower left.
     */
    
    glGenTextures(1, &(image_texture.texture_id));
    glBindTexture(GL_TEXTURE_2D, image_texture.texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_texture.width, image_texture.width, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image_texture.width, image_texture.height, GL_RGBA,
      GL_UNSIGNED_BYTE, img_rgba8888->pixels);

    //glBindTexture(GL_TEXTURE_2D, img_texture);
    SDL_FreeSurface(img_rgba8888);
    return image_error;
  }
}

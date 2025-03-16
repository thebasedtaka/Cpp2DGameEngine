#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "./Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager {
    public:
        //Load file into SDL_Tecture and renders into SDL Texture
        static SDL_Texture* LoadTexture(const char* fileName);
        //Renders texture with SDL_RenderCopyEx
        static void Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip);
};

#endif

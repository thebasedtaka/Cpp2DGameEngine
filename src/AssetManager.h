#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./TextureManager.h"
#include "./EntityManager.h"

class AssetManager {
    private:
        EntityManager* manager;
        std::map<std::string, SDL_Texture*> textures;
    public:
        AssetManager(EntityManager* manager);
        ~AssetManager();
        void ClearData();
        //add texture to map
        void AddTexture(std::string textureId, const char* filePath);
        //search map for texture
        SDL_Texture* GetTexture(std::string textureId);
};

#endif

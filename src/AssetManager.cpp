#include "./AssetManager.h"
#include "./Components/TransformComponent.h"
#include "AssetManager.h"
#include <iostream>

AssetManager::AssetManager(EntityManager* manager): manager(manager) {

}

AssetManager::~AssetManager()
{
}

void AssetManager::ClearData()
{
     textures.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath) { 
    textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return textures[textureId];
}


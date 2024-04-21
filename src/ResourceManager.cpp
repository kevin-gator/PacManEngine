#include "ResourceManager.hpp"

ResourceManager& ResourceManager::Instance() {
    if (mInstance == nullptr) {
        mInstance = new ResourceManager;
    }

    return *mInstance;
}

std::shared_ptr<SDL_Texture> ResourceManager::LoadTexture (SDL_Renderer* renderer, const char* filepath) {
    if (mTextureResources.find(filepath) == mTextureResources.end()) {
        SDL_Surface* pixels = SDL_LoadBMP(filepath);
        SDL_SetSurfaceColorKey(pixels,SDL_TRUE,SDL_MapRGB(pixels->format, 255, 255, 255));

        std::shared_ptr<SDL_Texture> texture = make_shared_texture(renderer, pixels);
        
        mTextureResources.insert({filepath, texture});
        
        SDL_DestroySurface(pixels);
    }

    return mTextureResources[filepath];
}

std::shared_ptr<SDL_Texture> make_shared_texture(SDL_Renderer* renderer, SDL_Surface* pixels) {
    SDL_Texture* pTexture =  SDL_CreateTextureFromSurface(renderer, pixels);
    if (pTexture == nullptr) {
        SDL_Log("Could not load texture from surface");
    }
    return std::shared_ptr<SDL_Texture>(pTexture, TextureFunctorDeleter());
}

ResourceManager* ResourceManager::mInstance = nullptr;
#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <filesystem>
#include <unordered_map>
#include <string>
#include "Scene.hpp"

/**
 * A functor for deleting SDL_Texture objects.
*/
struct TextureFunctorDeleter {
    void operator() (SDL_Texture* texture) const {
        SDL_DestroyTexture(texture);
    }
};

std::shared_ptr<SDL_Texture> make_shared_texture (SDL_Renderer* renderer, SDL_Surface* pixels);

/**
 * A singleton class for managing texture resources.
*/
struct ResourceManager {
    public:
        /**
         * Returns a new instance of the ResourceManager if one hasn't been created yet, or the existing
         * instance if it has been created.
        */
        static ResourceManager& Instance();
        /**
         * Loads a texture from the ResourceManager.
         * @param renderer a pointer to the renderer to use to load the texture.
         * @param filepath the path to the file to load the texture from.
        */
        std::shared_ptr<SDL_Texture> LoadTexture (SDL_Renderer* renderer, const char* filepath);
    private:
        ResourceManager() {}
        static ResourceManager* mInstance;
        std::unordered_map<const char*, std::shared_ptr<SDL_Texture>> mTextureResources;
};
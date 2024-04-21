#pragma once
#include "Component.hpp"

/**
 * A Component for rendering sprites by loading textures.
*/
struct SpriteRenderer : public Component {
    public:
        /**
         * Sets up the SpriteRenderer by creating the sprite.
         * @param renderer the SDL_Renderer to use to load the texture from a ResourceManager.
         * @param filepath the path to the file to load the texture from.
        */
        void CreateSprite(SDL_Renderer* renderer, const char* filepath);
        /**
         * Sets the current image file to load for the texture.
         * @param filepath the path to the file to load the texture from.
        */
        void SetSprite(const char* filepath);
        /**
         * Resizes the rectangle used for rendering the sprite.
         * @param width the width to set.
         * @param height the height to set.
        */
        void ResizeSprite(float width, float height);
        void Update(float deltaTime) override;
        void Render(SDL_Renderer* renderer) override;
        /**
         * Returns the file path of the current image being rendered by the SpriteRenderer.
         * @return the file path.
        */
        const char* GetFilePath();
        ComponentType GetType() override;
	private:
        SDL_Renderer* mRenderer;
		SDL_FRect mRectangle{0.0, 0.0, 32.0, 32.0};
        std::shared_ptr<SDL_Texture> mTexture;
        const char* mFilePath;
};
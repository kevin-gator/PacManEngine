#include "SpriteRenderer.hpp"
#include "Transform.hpp"
#include "ResourceManager.hpp"

ComponentType SpriteRenderer::GetType() {
    return SpriteRendererComponent;
}

void SpriteRenderer::CreateSprite(SDL_Renderer* renderer, const char* filepath) {
    mRenderer = renderer;
    SetSprite(filepath);
}

void SpriteRenderer::SetSprite(const char* filepath) {
    mFilePath = filepath;
    mTexture = ResourceManager::Instance().LoadTexture(mRenderer, filepath);
}

void SpriteRenderer::ResizeSprite(float width, float height) {
    mRectangle.w = width;
    mRectangle.h = height;
}

void SpriteRenderer::Update(float deltaTime) {
    std::shared_ptr<Transform> transformPtr = GetNeighborComponent<Transform>();
    if (transformPtr == nullptr) {
        SDL_Log("Component not found!");
        return;
    }
    
    mRectangle.x = transformPtr->GetX();
    mRectangle.y = transformPtr->GetY();
}

void SpriteRenderer::Render(SDL_Renderer* renderer) {
    if (mTexture == nullptr) {
        SDL_RenderRect(renderer, &mRectangle);
    } else {
        SDL_RenderTexture(renderer, mTexture.get(), nullptr, &mRectangle);
    }
}

const char* SpriteRenderer::GetFilePath() {
    return mFilePath;
}
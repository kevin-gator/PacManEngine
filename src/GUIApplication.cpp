#include "GUIApplication.hpp"
#include "ResourceManager.hpp"

GUIApplication::GUIApplication(float width, float height) : Application(width, height) {}

void GUIApplication::Input(float deltaTime) {
    mCurrKeyboardState = SDL_GetKeyboardState(nullptr);
    HandleKeyboardInputs(deltaTime);
    memcpy(mPrevKeyboardState, mCurrKeyboardState, SDL_NUM_SCANCODES);
}

void GUIApplication::RenderImage(const char* filePath, float x, float y, float w, float h) {
    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    std::shared_ptr<SDL_Texture> tex = ResourceManager::Instance().LoadTexture(mRenderer, filePath);
    if (tex == nullptr) {
        SDL_RenderRect(mRenderer, &rect);
    } else {
        SDL_RenderTexture(mRenderer, tex.get(), nullptr, &rect);
    }
}

bool GUIApplication::KeyPressStart(SDL_Scancode key) {
    return mCurrKeyboardState[key] && !mPrevKeyboardState[key];
}
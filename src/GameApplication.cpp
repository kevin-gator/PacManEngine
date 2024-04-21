#include "GameApplication.hpp"

GameApplication::GameApplication(float width, float height) : Application(width, height) {
    
}

void GameApplication::LoadScene(Scene scene) {
    mScene = std::make_shared<Scene>(scene);
}

void GameApplication::Input(float deltaTime) {
    mScene->Input(deltaTime);
}

void GameApplication::Update(float deltaTime) {
    mScene->Update(deltaTime);
    if (QuitConditionMet()) {
        mRun = false;
    }
}

void GameApplication::Render() {
    /*SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);*/

    mScene->Render(mRenderer);
}
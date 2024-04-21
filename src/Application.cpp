#include "Application.hpp"

Application::Application(float width, float height) {
    StartUp(width, height);
}

void Application::StartUp(float width, float height) {
    SDL_Window* mWindow = SDL_CreateWindow("Application", width,height,
                                            SDL_WINDOW_OPENGL);
    mRenderer = SDL_CreateRenderer(mWindow, NULL, SDL_RENDERER_ACCELERATED);
    if (mRenderer == nullptr) {
        SDL_Log("Error creating renderer");
    }
    mWidth = width;
    mHeight = height;
}

Application::~Application() {
    ShutDown();
}

void Application::ShutDown() {
    SDL_Quit();
}

bool Application::QuitConditionMet() {
    return false;
}

void Application::Run(float targetFPS) {
    Uint64 lastTime, currentTime;

    lastTime = SDL_GetTicks();
    Uint64 framesElapsed=0;
    float deltaTime = 1.0f/targetFPS;
    while(mRun) {
        Uint64 startOfFrame=SDL_GetTicks();

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                SDL_Log("Program quit %llu", event.quit.timestamp);
                mRun=false;
            }
        }

        if (deltaTime <= 1.1 * (1/targetFPS)) {
            Input(deltaTime);
            Update(deltaTime);
            SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(mRenderer);
            SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            Render();
            SDL_RenderPresent(mRenderer);
        }

        Uint64 elapsedTime=SDL_GetTicks()-startOfFrame;
        framesElapsed++;

        currentTime = SDL_GetTicks();
        if (elapsedTime < (1000/targetFPS)) {
            Uint64 delay = (1000/targetFPS)-elapsedTime;
            SDL_Delay(delay);
        }

        if (currentTime > lastTime+1000) {
            deltaTime = 1.0f/framesElapsed;
            framesElapsed=0;
            lastTime=SDL_GetTicks();
        }
    }
}
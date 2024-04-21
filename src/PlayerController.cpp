#include "PlayerController.hpp"
#include "Rigidbody.hpp"
#include "SpriteRenderer.hpp"
#include "GameEntity.hpp"
#include "Ghost.hpp"
#include <SDL3/SDL.h>

ComponentType PlayerController::GetType() {
    return PlayerControllerComponent;
}

void PlayerController::Input(float deltaTime) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    
    std::shared_ptr<Rigidbody> rigidbody = GetNeighborComponent<Rigidbody>();
    if (rigidbody == nullptr) {
        SDL_Log("Rigidbody component not found!");
        return;
    }
    std::shared_ptr<SpriteRenderer> spriteRenderer = GetNeighborComponent<SpriteRenderer>();
    if (spriteRenderer == nullptr) {
        SDL_Log("SpriteRenderer component not found!");
        return;
    }
    if (state[SDL_SCANCODE_LEFT]) {
        rigidbody->QueueMove(-mSpeed * deltaTime, 0);
        spriteRenderer->SetSprite("./assets/art/pacman-left.bmp");
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        rigidbody->QueueMove(mSpeed * deltaTime, 0);
        spriteRenderer->SetSprite("./assets/art/pacman-right.bmp");
    }
    if (state[SDL_SCANCODE_UP]) {
        rigidbody->QueueMove(0, -mSpeed * deltaTime);
        spriteRenderer->SetSprite("./assets/art/pacman-up.bmp");
    }
    if (state[SDL_SCANCODE_DOWN]) {
        rigidbody->QueueMove(0, mSpeed * deltaTime);
        spriteRenderer->SetSprite("./assets/art/pacman-down.bmp");
    }
}

void PlayerController::Update(float deltaTime) {
    if (mPoweredUp) {
        mFrightenTimer += deltaTime;
        if (mFrightenTimer >= mFrightenDuration) {
            mFrightenTimer = 0;
            mPoweredUp = false;
        }
    }
}

void PlayerController::SetGhosts(std::vector<std::shared_ptr<GameEntity>> ghosts) {
    mGhosts = ghosts;
}

void PlayerController::SetWinScore(int winScore) {
    mWinScore = winScore;
}

bool PlayerController::IsGameWon() {
    return mScore >= mWinScore;
}

bool PlayerController::IsGameLost() {
    return mGameOver;
}

void PlayerController::OnCollisionWithEntity(std::shared_ptr<GameEntity> other) {
    if (other->HasTag("Coin")) { 
        mScore += 1;
        other->Disable();
    }
    if (other->HasTag("PowerUp") && !mPoweredUp) {
        for (auto ghost : mGhosts) {
            ghost->GetComponent<Ghost>(GhostComponent)->Frighten(mFrightenDuration);
        }
        mPoweredUp = true;
        mFrightenTimer = 0;
    }
    if (other->HasTag("Ghost")) {
        if (mPoweredUp) {
            other->Disable();
        } else {
            mGameOver = true;
        }
    }
}
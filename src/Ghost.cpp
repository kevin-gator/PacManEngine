#include <cmath>
#include "Ghost.hpp"
#include "Rigidbody.hpp"
#include "GameEntity.hpp"
#include "SpriteRenderer.hpp"
#include <string>

void Ghost::SetAwakeDelay(float delay) {
    mAwakeDelay = delay;
}

void Ghost::Update(float deltaTime) {
    std::shared_ptr<Rigidbody> rigidbody = GetNeighborComponent<Rigidbody>();
    if (rigidbody == nullptr) {
        SDL_Log("Rigidbody component not found!");
        return;
    }
    if (mState != Frightened) {
        mTimer += deltaTime;
    } else {
        mFrightenedTimer += deltaTime;
    }
    if (mState == Frightened && mFrightenedTimer > mFrightenDuration) {
        mSpeed = mDefaultSpeed;
        mState = mLastUnfrightenedState;
        SetSprite(mPrevSpritePath);
    }
    if (mTimer < mAwakeDelay) {
        return;
    }
    mPrevFrameState = mState;
    if (mState == Scatter && mTimer > mLastAISwitchTime + 5) {
        mLastAISwitchTime = mTimer;
        mState = Chase;
    }
    if (mState == Chase && mTimer > mLastAISwitchTime + 20) {\
        mLastAISwitchTime = mTimer;
        mState = Scatter;
    }
    switch (mDirection) {
        case Up:
            rigidbody->QueueMove(0, -mSpeed * deltaTime);
            break;
        case Right:
            rigidbody->QueueMove(mSpeed * deltaTime, 0);
            break;
        case Down:
            rigidbody->QueueMove(0, mSpeed * deltaTime);
            break;
        case Left:
            rigidbody->QueueMove(-mSpeed * deltaTime, 0);
            break;
    }
    
    if (mState != Scatter) {
        mTargetX = mPlayer->GetComponent<Transform>(TransformComponent)->GetX();
        mTargetY = mPlayer->GetComponent<Transform>(TransformComponent)->GetY();
    } else {
        mTargetX = mScatterTargetX;
        mTargetY = mScatterTargetY;
    }

    Move(deltaTime);
}

void Ghost::SetPlayer(std::shared_ptr<GameEntity> player) {
    mPlayer = player;
}

void Ghost::SetNavMesh(std::vector<std::vector<bool>> navMesh, float gridSize) {
    mNavMesh = navMesh;
    mGridSize = gridSize;
}

void Ghost::SetScatterTarget(float x, float y) {
    mScatterTargetX = x;
    mScatterTargetY = y;
}

void Ghost::Frighten(float duration) {
    mLastUnfrightenedState = mState;
    mPrevFrameState = mState;
    mState = Frightened;
    mFrightenedTimer = 0;
    mFrightenDuration = duration;
    mSpeed = mFrightenedSpeed;
    SetSprite("./assets/art/ghost-frightened.bmp");
}

void Ghost::SetSprite(const char* filePath) {
    std::shared_ptr<SpriteRenderer> spriteRenderer = GetNeighborComponent<SpriteRenderer>();
    if (spriteRenderer == nullptr) {
        SDL_Log("SpriteRenderer component not found!");
        return;
    }
    mPrevSpritePath = spriteRenderer->GetFilePath();
    spriteRenderer->SetSprite(filePath);
}

void Ghost::Move(float deltaTime) {
    std::shared_ptr<Transform> transform = GetNeighborComponent<Transform>();
    if (transform == nullptr) {
        SDL_Log("Transform component not found!");
        return;
    }
    float x = transform->GetX();
    float y = transform->GetY();
    float normalizedX = (x / mGridSize);
    float normalizedY = (y / mGridSize);
    float ceilX = ceil(normalizedX);
    float floorX = floor(normalizedX);
    float ceilY = ceil(normalizedY);
    float floorY = floor(normalizedY);
    float diffX;
    float diffY;
    if (ceilX > floorX) {
        diffX = ceilX - normalizedX;
    } else {
        diffX = normalizedX - floorX;
    }
    if (ceilY > floorY) {
        diffY = ceilY - normalizedY;
    } else {
        diffY = normalizedY - floorY;
    }
    float f = 20;
    if (diffX > f * deltaTime || diffY > f * deltaTime) {
        return;
    }
    int roundedX = round(normalizedX);
    if (roundedX > 18) {
        roundedX = 0;
    }
    int roundedY = round(normalizedY);
    if (roundedY > 18) {
        roundedY = 0;
    }
    bool up = false;
    bool right = false;
    bool down = false;
    bool left = false;
    if (roundedY > 0) {
        auto row = mNavMesh[roundedY - 1];
        bool val = row[roundedX];
        up = !val;
    }
    if (roundedX < 18) {
        auto row = mNavMesh[roundedY];
        bool val = row[roundedX + 1];
        right = !val;
    }
    if (roundedY < 18) {
        auto row = mNavMesh[roundedY + 1];
        bool val = row[roundedX];
        down = !val;
    }
    if (roundedX > 0) {
        auto row = mNavMesh[roundedY];
        bool val = row[roundedX - 1];
        left = !val;
    }
    if (mState == mPrevFrameState) {
        switch (mDirection) {
            case Up:
                down = false;
                break;
            case Right:
                left = false;
                break;
            case Down:
                up = false;
                break;
            case Left:
                right = false;
                break;
        }
    }

    if (!up && !right && !down && !left) {
        return;
    }
    std::map<Direction, std::vector<float>> possibleDirections;
    if (up) {
        std::vector<float> coord;
        coord.push_back(roundedX * mGridSize);
        coord.push_back((roundedY - 1) * mGridSize);
        possibleDirections.insert({Up, coord});
    }
    if (right) {
        std::vector<float> coord;
        coord.push_back((roundedX + 1) * mGridSize);
        coord.push_back(roundedY * mGridSize);
        possibleDirections.insert({Right, coord});
    }
    if (down) {
        std::vector<float> coord;
        coord.push_back(roundedX * mGridSize);
        coord.push_back((roundedY + 1) * mGridSize);
        possibleDirections.insert({Down, coord});
    }
    if (left) {
        std::vector<float> coord;
        coord.push_back((roundedX - 1) * mGridSize);
        coord.push_back(roundedY * mGridSize);
        possibleDirections.insert({Left, coord});
    }
    Direction directionToMove;
    float distToTarget = 99999;
    if (mState == Frightened) {
        distToTarget = 0;
    }
    for (auto& [key, value] : possibleDirections) {
        float distX = abs(mTargetX - value[0]);
        float distY = abs(mTargetY - value[1]);
        float dist = sqrt((distX * distX) + (distY * distY));
        if ((mState != Frightened && dist < distToTarget) || (mState == Frightened && dist > distToTarget)) {
            distToTarget = dist;
            directionToMove = key;
        }
    }
    if (mDirection != directionToMove) {
        transform->SetPosition(roundedX * mGridSize, roundedY * mGridSize);
    }
    mDirection = directionToMove;
}

ComponentType Ghost::GetType() {
    return GhostComponent;
}

void Ghost::SetTarget(float x, float y) {
    mTargetX = x;
    mTargetY = y;
}
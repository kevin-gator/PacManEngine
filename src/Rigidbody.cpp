#include "Rigidbody.hpp"
#include "Transform.hpp"
#include <cmath>

ComponentType Rigidbody::GetType() {
    return RigidbodyComponent;
}

void Rigidbody::SetGridSize(float gridSize) {
    mGridSize = gridSize;
    mSceneWidth = gridSize * 19;
    mSceneHeight = gridSize * 19;
}

void Rigidbody::QueueMove(float x, float y) {
    std::shared_ptr<Transform> transformPtr = GetNeighborComponent<Transform>();
    if (transformPtr == nullptr) {
        SDL_Log("Transform component not found!");
        return;
    }
    mQueuedMoveX = x;
    mQueuedMoveY = y;
}

void Rigidbody::PerformMove(float deltaTime) {
    std::shared_ptr<Transform> transformPtr = GetNeighborComponent<Transform>();
    if (transformPtr == nullptr) {
        SDL_Log("Transform component not found!");
        return;
    }
    if (mQueuedMoveX != 0 || mQueuedMoveY != 0)
        transformPtr->Move(mQueuedMoveX * deltaTime, mQueuedMoveY * deltaTime);
    float moveMagnitude = sqrt(abs(mQueuedMoveX * mQueuedMoveX) + abs(mQueuedMoveY * mQueuedMoveY));
    float snapThreshold = 0.0155 * moveMagnitude; //0.155 * moveMagnitude;
    mQueuedMoveX = 0;
    mQueuedMoveY = 0;
    if (transformPtr->GetX() <= 0) {
        transformPtr->SetPosition(mSceneWidth - snapThreshold - 0.1, transformPtr->GetY());
    }
    if (transformPtr->GetX() >= mSceneWidth) {
        transformPtr->SetPosition(mGridSize, transformPtr->GetY());
    }
    if (transformPtr->GetY() <= 0) {
        transformPtr->SetPosition(transformPtr->GetX(), mSceneHeight -snapThreshold - 0.1);
    }
    if (transformPtr->GetY() >= mSceneHeight) {
        transformPtr->SetPosition(transformPtr->GetX(), mGridSize);
    }
    float x = transformPtr->GetX();
    float y = transformPtr->GetY();
    float normalizedX = (x / mGridSize);
    float normalizedY = (y / mGridSize);
    int roundedX = round(normalizedX);
    int roundedY = round(normalizedY);
    float snapX = roundedX * mGridSize;
    float snapY = roundedY * mGridSize;
    float distX = abs(x - snapX);
    float distY = abs(y - snapY);
    float dist = sqrt((distX * distX) + (distY * distY));
    if (dist < snapThreshold && dist > 0) {
        //SDL_Log("SNAPPING: %f, %f", snapX, snapY);
        transformPtr->SetPosition(snapX, snapY);
    }
}

void Rigidbody::CorrectCollision(std::shared_ptr<Transform> thisTransform, 
    std::shared_ptr<Transform> otherTransform, SDL_FRect* intersection) {
    float diffX = thisTransform->GetX() - otherTransform->GetX();
    float diffY = thisTransform->GetY() - otherTransform->GetY();
    if (abs(diffX) > abs(diffY)) {
        float correctX = intersection->w;
        if (diffX >= 0) {
            thisTransform->Move(correctX, 0);
        } else {
            thisTransform->Move(-correctX, 0);
        }
    } else {
        float correctY = intersection->h;
        if (diffY >= 0) {
            thisTransform->Move(0, correctY);
        } else {
            thisTransform->Move(0, -correctY);
        }
    }
}
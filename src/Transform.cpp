#include "Transform.hpp"
#include "GameEntity.hpp"

ComponentType Transform::GetType() {
    return TransformComponent;
}

void Transform::SetPosition(float x, float y) {
    mX = x;
    mY = y;
    //SDL_Log("Setting posn: %f, %f", x, y);
}

void Transform::Move(float x, float y) {
    SetPosition(mX + x, mY + y);

    if (mConstrainChildren) {
        auto children = mGameEntity->GetChildren();
        for (auto & [key, value] : children) {
            auto transform = children[key]->GetComponent<Transform>(TransformComponent);
            if (transform != nullptr) {
                transform->Move(x, y);
            }
        }
    }
}

float Transform::GetX() {
    return mX;
}

float Transform::GetY() {
    return mY;
}

void Transform::SetConstrainChildren(bool value) {
    mConstrainChildren = value;
}
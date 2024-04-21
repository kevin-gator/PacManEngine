#include "Collider.hpp"
#include "Transform.hpp"
#include "Rigidbody.hpp"
#include "GameEntity.hpp"

void Collider::Update(float deltaTime) {
    std::shared_ptr<Transform> transformPtr = GetNeighborComponent<Transform>();
    if (transformPtr == nullptr) {
        SDL_Log("Component not found!");
        return;
    }
    
    mRectangle.x = transformPtr->GetX();
    mRectangle.y = transformPtr->GetY();
}

ComponentType Collider::GetType() {
    return ColliderComponent;
}

SDL_FRect Collider::GetRectangle() {
    return mRectangle;
}

void Collider::ResizeCollider(float width, float height) {
    mRectangle.h = height;
    mRectangle.w = width;
}

void Collider::SetIsTrigger(bool isTrigger) {
    mIsTrigger = isTrigger;
}

void Collider::AddIgnoreTag(std::string tag) {
    mIgnoreTags.push_back(tag);
}

bool Collider::IsTrigger() {
    return mIsTrigger;
}

bool Collider::CollidesWith(std::shared_ptr<Collider> other) {
    SDL_FRect otherR = other->GetRectangle();
    return SDL_HasRectIntersectionFloat(&otherR, &mRectangle);
}

void Collider::OnCollisionWith(std::shared_ptr<Collider> other) {
    auto otherEntity = other->GetGameEntity();
    for (std::string tag : mIgnoreTags) {
        if (otherEntity->HasTag(tag)) {
            return;
        }
    }
    std::shared_ptr<Rigidbody> rigidbodyPtr = GetNeighborComponent<Rigidbody>();
    if (rigidbodyPtr != nullptr && !mIsTrigger && !other->IsTrigger()) {
        SDL_FRect intersection;
        SDL_FRect otherRect = other->GetRectangle();
        SDL_FRect thisRect = GetRectangle();
        SDL_GetRectIntersectionFloat(&otherRect, &thisRect, &intersection);
        std::shared_ptr<Transform> thisTransform= GetNeighborComponent<Transform>();
        if (thisTransform == nullptr) {
            SDL_Log("Component not found!");
            return;
        }
        std::shared_ptr<Transform> otherTransform= other->GetNeighborComponent<Transform>();
        if (otherTransform == nullptr) {
            SDL_Log("Component not found!");
            return;
        }

        rigidbodyPtr->CorrectCollision(thisTransform, otherTransform, &intersection);
    }

    mGameEntity->OnCollisionWithEntity(otherEntity);
}
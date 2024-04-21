#include "Component.hpp"
#include "Transform.hpp"
#include "Rigidbody.hpp"
#include "GameEntity.hpp"
#include "SpriteRenderer.hpp"

Component::Component() {

}

Component::~Component() {

}

ComponentType Component::GetType() {
    return NoComponent;
}

void Component::Input(float deltaTime) {

}

void Component::Update(float deltaTime) {

}

void Component::Render(SDL_Renderer* renderer) {

}

void Component::Enable() {
    mEnabled = true;
}

void Component::Disable() {
    mEnabled = false;
}

bool Component::IsEnabled() {
    return mEnabled;
}

void Component::SetGameEntity(std::shared_ptr<GameEntity> gameEntity) {
    mGameEntity = gameEntity;
}

std::shared_ptr<GameEntity> Component::GetGameEntity() {
    return mGameEntity;
}

template<> std::shared_ptr<Transform> Component::GetNeighborComponent<Transform>() {
    std::shared_ptr<Transform> transform = mGameEntity->GetComponent<Transform>(TransformComponent);
    return transform;
}

template<> std::shared_ptr<Rigidbody> Component::GetNeighborComponent<Rigidbody>() {
    std::shared_ptr<Rigidbody> rigidbody = mGameEntity->GetComponent<Rigidbody>(RigidbodyComponent);
    return rigidbody;
}

template<> std::shared_ptr<SpriteRenderer> Component::GetNeighborComponent<SpriteRenderer>() {
    std::shared_ptr<SpriteRenderer> spriteRenderer = mGameEntity->GetComponent<SpriteRenderer>(SpriteRendererComponent);
    return spriteRenderer;
}
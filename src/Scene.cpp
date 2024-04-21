#include "Scene.hpp"
#include <vector>

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::Input(float deltaTime) {
    for (auto& [key,value] : mGameEntities) {
        mGameEntities[key]->Input(deltaTime);
    }
}

void Scene::Update(float deltaTime) {
    for (auto& [key,value] : mGameEntities) {
        mGameEntities[key]->Update(deltaTime);
    }
    ProcessRigidbodies(deltaTime);
    ProcessCollisions();
}

void Scene::Render(SDL_Renderer* renderer) {
    for (auto& [key,value] : mGameEntities) {
        mGameEntities[key]->Render(renderer);
    }
}

void Scene::AddGameEntity(std::string name, std::shared_ptr<GameEntity> gameEntity) {
    mGameEntities.insert({name, gameEntity});
}

std::shared_ptr<GameEntity> Scene::GetGameEntity(std::string name) {
    if (mGameEntities.find(name) == mGameEntities.end()) {
        SDL_Log("Entity not found");
        return nullptr;
    }
    return mGameEntities[name];
}

void Scene::ProcessRigidbodies(float deltaTime) {
    std::vector<std::shared_ptr<Rigidbody>> rigidbodies;
    auto rigidbodiesPtr = std::make_shared<std::vector<std::shared_ptr<Rigidbody>>>(rigidbodies);
    for (auto& [key,value] : mGameEntities) {
        ProcessRigidbodiesHelper(mGameEntities[key], rigidbodiesPtr);
    }
    for (auto& rigidbodyPtr : *rigidbodiesPtr) {
        rigidbodyPtr->PerformMove(deltaTime);
    }
}

void Scene::ProcessRigidbodiesHelper(std::shared_ptr<GameEntity> gameEntity, 
    std::shared_ptr<std::vector<std::shared_ptr<Rigidbody>>> rigidbodies) {
    if (!gameEntity->IsEnabled()) {
        return;
    }
    auto rigidbodyPtr = gameEntity->GetComponent<Rigidbody>(RigidbodyComponent);
    if (rigidbodyPtr != nullptr) {
        rigidbodies->push_back(rigidbodyPtr);
    }
    auto children = gameEntity->GetChildren();
    for (auto& [key,value] : children) {
        ProcessRigidbodiesHelper(children[key], rigidbodies);
    }
}

void Scene::ProcessCollisions() {
    std::vector<std::shared_ptr<Collider>> colliders;
    auto collidersPtr = std::make_shared<std::vector<std::shared_ptr<Collider>>>(colliders);
    for (auto& [key,value] : mGameEntities) {
        ProcessCollisionsHelper(mGameEntities[key], collidersPtr);
    }
    for (int i = 0; i < collidersPtr->size(); ++i) {
        auto& colliderA = collidersPtr->at(i);
        for (int j = i + 1; j < collidersPtr->size(); ++j) {
            auto& colliderB = collidersPtr->at(j);
            if (colliderA->CollidesWith(colliderB)) {
                colliderA->OnCollisionWith(colliderB);
                colliderB->OnCollisionWith(colliderA);
            }
        }
    }
}
void Scene::ProcessCollisionsHelper(std::shared_ptr<GameEntity> gameEntity, 
    std::shared_ptr<std::vector<std::shared_ptr<Collider>>> colliders) {
    if (!gameEntity->IsEnabled()) {
        return;
    }
    auto colliderPtr = gameEntity->GetComponent<Collider>(ColliderComponent);
    if (colliderPtr != nullptr) {
        colliders->push_back(colliderPtr);
    }
    auto children = gameEntity->GetChildren();
    for (auto& [key,value] : children) {
        ProcessCollisionsHelper(children[key], colliders);
    }
}
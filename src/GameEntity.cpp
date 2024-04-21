#include "GameEntity.hpp"
#include "Collider.hpp"

GameEntity::GameEntity() {
    
}

GameEntity::~GameEntity() {

}

void GameEntity::Input(float deltaTime) {
    if (!mEnabled) { return; }
    for (auto& [key, value] : mChildEntities) {
        mChildEntities[key]->Input(deltaTime);
    }
    for (auto& [key,value] : mComponents) {
        if (mComponents[key]->IsEnabled()) {
            mComponents[key]->Input(deltaTime);
        }
    }
}

void GameEntity::Update(float deltaTime) {
    if (!mEnabled) { return; }
    for (auto& [key, value] : mChildEntities) {
        mChildEntities[key]->Update(deltaTime);
    }
    for (auto& [key, value] : mComponents) {
        if (mComponents[key]->IsEnabled()) {
            mComponents[key]->Update(deltaTime);
        }
    }
}

void GameEntity::Render(SDL_Renderer* renderer) {
    for (auto& [key, value] : mChildEntities) {
        mChildEntities[key]->Render(renderer);
    }
    if (!mEnabled) { return; }
    for (auto& [key, value] : mComponents) {
        if (mComponents[key]->IsEnabled()) {
            mComponents[key]->Render(renderer);
        }
    }
}

void GameEntity::AddChildEntity(std::string name, std::shared_ptr<GameEntity> child) {
    mChildEntities.insert({name, child});
}

std::shared_ptr<GameEntity> GameEntity::GetChildEntity(std::string name) {
    if (mChildEntities.find(name) == mChildEntities.end()) {
        SDL_Log("No child entity with the given name exists!");
        return nullptr;
    }
    return mChildEntities[name];
}

std::map<std::string, std::shared_ptr<GameEntity>> 
GameEntity::GetChildren() {
    return mChildEntities;
}

void GameEntity::Enable() {
    mEnabled = true;
}

void GameEntity::Disable() {
    mEnabled = false;
    for (auto& [key, value] : mChildEntities) {
        mChildEntities[key]->Disable();
    }
}

bool GameEntity::IsEnabled() {
    return mEnabled;
}

void GameEntity::OnCollisionWithEntity(std::shared_ptr<GameEntity> other) {
    for (auto& [key, value] : mComponents) {
        mComponents[key]->OnCollisionWithEntity(other);
    }
}

void GameEntity::AddTag(std::string tag) {
    if (HasTag(tag)) { return; }
    mTags.push_back(tag);
}

bool GameEntity::HasTag(std::string tag) {
    return std::find(mTags.begin(), mTags.end(), tag)!=mTags.end();
}
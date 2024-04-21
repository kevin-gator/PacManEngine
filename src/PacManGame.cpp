#include "PacManGame.hpp"
#include "PlayerController.hpp"

PacManGame::PacManGame(float width, float height) : GameApplication(width, height) {
    
}
void PacManGame::LoadLevelFile(std::string file) {
    mLevelManager = LevelManager(mWidth / 19, mRenderer);
    LoadScene(GetSceneFromLevelFile(file));
}

bool PacManGame::QuitConditionMet() {
    std::shared_ptr<GameEntity> playerEntity = mScene->GetGameEntity("Player");
    if (playerEntity == nullptr) {
        return false;
    }
    std::shared_ptr<PlayerController> playerController = playerEntity->GetComponent<PlayerController>(PlayerControllerComponent);
    if (playerController == nullptr) {
        return false;
    }
    return playerController->IsGameWon() || playerController->IsGameLost();
}

Scene PacManGame::GetSceneFromLevelFile(std::string fileName) {
    return mLevelManager.LoadLevelFile(fileName);
}
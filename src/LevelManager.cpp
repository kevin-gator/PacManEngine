#include <filesystem>
#include <fstream>
#include <vector>
#include "LevelManager.hpp"
#include "Transform.hpp"
#include "SpriteRenderer.hpp"
#include "Collider.hpp"
#include "Rigidbody.hpp"
#include "PlayerController.hpp"
#include "Ghost.hpp"
#include "SaveLoadUtilities.hpp"

LevelManager::LevelManager(float gridSize, SDL_Renderer* renderer) {
    mGridSize = gridSize;
    mCoinCount = 0;
    mPowerUpCoinCount = 0;
    mWallCount = 0;
    mPlayerCount = 0;
    mInkyCount = 0;
    mBlinkyCount = 0;
    mPinkyCount = 0;
    mClydeCount = 0;
    mGateCount = 0;
    mRenderer = renderer;
}

Scene LevelManager::LoadLevelFile(std::string fileName) {
    return LoadSceneFromTileGrid(LoadTileGridFromFile(fileName));
}

Scene LevelManager::LoadSceneFromTileGrid(std::vector<std::vector<TileType>> tileGrid) {
    Scene scene = Scene();
    for (int y = 0; y < tileGrid.size(); ++y) {
        auto row = tileGrid[y];
        std::vector<bool> navMeshRow;
        for (int x = 0; x < row.size(); ++x) {
            float worldX = (x * mGridSize);
            float worldY = (y * mGridSize);
            TileType tile = row[x];
            bool isWall = false;
            switch (tile) {
                case Empty:
                    break;
                case Coin:
                    mCoinCount += 1;
                    break;
                case PowerUpCoin:
                    mPowerUpCoinCount += 1;
                    break;
                case Wall:
                    navMeshRow.push_back(true);
                    isWall = true;
                    mWallCount += 1;
                    break;
                case Player:
                    if (mPlayerCount >= 1) {
                        throw std::invalid_argument("More than one player is not allowed!");
                    }
                    mPlayerCount += 1;
                    break;
                case Inky:
                if (mInkyCount >= 1) {
                        throw std::invalid_argument("More than one Inky is not allowed!");
                    }
                    mInkyCount += 1;
                    break;
                case Blinky:
                    if (mBlinkyCount >= 1) {
                        throw std::invalid_argument("More than one Blinky is not allowed!");
                    }
                    mBlinkyCount += 1;
                    break;
                case Pinky:
                    if (mPinkyCount >= 1) {
                        throw std::invalid_argument("More than one Pinky is not allowed!");
                    }
                    mPinkyCount += 1;
                    break;
                case Clyde:
                    if (mClydeCount >= 1) {
                        throw std::invalid_argument("More than one Clyde is not allowed!");
                    }
                    mClydeCount += 1;
                    break;
                case Gate:
                    mGateCount += 1;
                    break;
            }
            if (!isWall) {
                navMeshRow.push_back(false);
            }
            AddTileToScene(tile, scene, worldX, worldY);
        }
        mNavMesh.push_back(navMeshRow);
    }
    mPlayerEntity->GetComponent<PlayerController>(PlayerControllerComponent)->SetWinScore(mCoinCount + mPowerUpCoinCount);
    for (auto ghost : mGhosts) {
        ghost->GetComponent<Ghost>(GhostComponent)->SetPlayer(mPlayerEntity);
        ghost->GetComponent<Ghost>(GhostComponent)->SetNavMesh(mNavMesh, mGridSize);
    }
    mPlayerEntity->GetComponent<PlayerController>(PlayerControllerComponent)->SetGhosts(mGhosts);
    return scene;
}

void LevelManager::AddTileToScene(TileType tile, Scene& scene, float x, float y) {
    std::string name;
    switch (tile) {
        case Coin:
            name = "Coin";
            name.append(std::to_string(mCoinCount));
            scene.AddGameEntity(name, GenerateCoinTile(x, y));
            return;
        case PowerUpCoin:
            name = "PowerUpCoin";
            name.append(std::to_string(mPowerUpCoinCount));
            scene.AddGameEntity(name, GeneratePowerUpCoinTile(x, y));
        case Wall:
            name = "Wall";
            name.append(std::to_string(mWallCount));
            scene.AddGameEntity(name, GenerateWallTile(x, y));
            return;
        case Player:
            scene.AddGameEntity("Player", GeneratePlayerTile(x, y));
            return;
        case Inky:
            scene.AddGameEntity("Inky", GenerateInkyTile(x, y));
            return;
        case Blinky:
            scene.AddGameEntity("Blinky", GenerateBlinkyTile(x, y));
            return;
        case Pinky:
            scene.AddGameEntity("Pinky", GeneratePinkyTile(x, y));
            return;
        case Clyde:
            scene.AddGameEntity("Clyde", GenerateClydeTile(x, y));
            return;
        case Gate:
            name = "Gate";
            name.append(std::to_string(mGateCount));
            scene.AddGameEntity(name, GenerateGateTile(x, y));
        default:
            return;
    }
}

std::shared_ptr<GameEntity> LevelManager::GenerateCoinTile(float x, float y) {
    std::shared_ptr<GameEntity> ge = GenerateEntityAt(x, y);
    AddSpriteRenderer(ge, "./assets/art/coin.bmp", 1);
    AddCollider(ge, 1, true);
    ge->AddTag("Coin");
    return ge;
}

std::shared_ptr<GameEntity> LevelManager::GeneratePowerUpCoinTile(float x, float y) {
    std::shared_ptr<GameEntity> ge = GenerateEntityAt(x, y);
    AddSpriteRenderer(ge, "./assets/art/powerup-coin.bmp", 1);
    AddCollider(ge, 1, true);
    ge->AddTag("Coin");
    ge->AddTag("PowerUp");
    return ge;
}

std::shared_ptr<GameEntity> LevelManager::GenerateWallTile(float x, float y) {
    std::shared_ptr<GameEntity> ge = GenerateEntityAt(x, y);
    AddSpriteRenderer(ge, "./assets/art/wall.bmp", 1);
    AddCollider(ge, 1, false);
    return ge;
}

std::shared_ptr<GameEntity> LevelManager::GeneratePlayerTile(float x, float y) {
    std::shared_ptr<GameEntity> ge = GenerateEntityAt(x, y);
    AddPlayerController(ge);
    AddSpriteRenderer(ge, "./assets/art/pacman-right.bmp", 1);
    AddCollider(ge, 0.9, false);
    AddRigidbody(ge);
    mPlayerEntity = ge;
    return ge;
}

std::shared_ptr<GameEntity> LevelManager::GenerateGateTile(float x, float y) {
    std::shared_ptr<GameEntity> ge = GenerateEntityAt(x, y);
    std::vector<std::string> ignoreTags;
    ignoreTags.push_back("Ghost");
    AddCollider(ge, 1, false, ignoreTags);
    AddSpriteRenderer(ge, "./assets/art/gate.bmp", 1);
    ge->AddTag("Gate");
    return ge;
}

std::shared_ptr<GameEntity> LevelManager::GenerateInkyTile(float x, float y) {
    std::shared_ptr<GameEntity> ge = GenerateGhostTemplate(x, y);
    AddSpriteRenderer(ge, "./assets/art/inky.bmp", 1);
    AddGhost(ge, 8, 0, 0);
    return ge;
}

std::shared_ptr<GameEntity> LevelManager::GenerateBlinkyTile(float x, float y) {
    std::shared_ptr<GameEntity> ge = GenerateGhostTemplate(x, y);
    AddSpriteRenderer(ge, "./assets/art/blinky.bmp", 1);
    AddGhost(ge, 1, mGridSize * 19, 0);
    return ge;
}

std::shared_ptr<GameEntity> LevelManager::GeneratePinkyTile(float x, float y) {
    std::shared_ptr<GameEntity> ge = GenerateGhostTemplate(x, y);
    AddSpriteRenderer(ge, "./assets/art/pinky.bmp", 1);
    AddGhost(ge, 13, mGridSize * 19, mGridSize * 19);
    return ge;
}

std::shared_ptr<GameEntity> LevelManager::GenerateClydeTile(float x, float y) {
    std::shared_ptr<GameEntity> ge = GenerateGhostTemplate(x, y);
    AddSpriteRenderer(ge, "./assets/art/clyde.bmp", 1);
    AddGhost(ge, 18, 0, mGridSize * 19);
    return ge;
}

std::shared_ptr<GameEntity> LevelManager::GenerateGhostTemplate(float x, float y) {
    std::shared_ptr<GameEntity> ge = GenerateEntityAt(x, y);
    std::vector<std::string> ignoreTags;
    ignoreTags.push_back("Ghost");
    ignoreTags.push_back("Gate");
    AddCollider(ge, 0.99, false, ignoreTags);
    AddRigidbody(ge);
    ge->AddTag("Ghost");
    mGhosts.push_back(ge);
    return ge;
}

std::shared_ptr<GameEntity> LevelManager::GenerateEntityAt(float x, float y) {
    GameEntity entity = GameEntity();
    std::shared_ptr<GameEntity> entityPtr = std::make_shared<GameEntity>(entity);
    
    Transform component = Transform();
    component.SetPosition(x, y);

    std::shared_ptr<Transform> componentPtr = std::make_shared<Transform>(component);
    entityPtr->AddComponent(componentPtr);
    return entityPtr;
}

void LevelManager::AddSpriteRenderer(std::shared_ptr<GameEntity> ge, const char* filePath, float size) {
    SpriteRenderer component = SpriteRenderer();
    component.CreateSprite(mRenderer, filePath);
    component.ResizeSprite(size * mGridSize, size * mGridSize);

    std::shared_ptr<SpriteRenderer> componentPtr = std::make_shared<SpriteRenderer>(component);
    ge->AddComponent(componentPtr);
}

void LevelManager::AddCollider(std::shared_ptr<GameEntity> ge, float size, bool isTrigger, 
    std::vector<std::string> ignoreTags) {
    Collider component = Collider();
    component.ResizeCollider(size * mGridSize, size * mGridSize);
    component.SetIsTrigger(isTrigger);
    for (std::string tag : ignoreTags) {
        component.AddIgnoreTag(tag);
    }

    std::shared_ptr<Collider> componentPtr = std::make_shared<Collider>(component);
    ge->AddComponent(componentPtr);
}

void LevelManager::AddCollider(std::shared_ptr<GameEntity> ge, float size, bool isTrigger) {
    Collider component = Collider();
    component.ResizeCollider(size * mGridSize, size * mGridSize);
    component.SetIsTrigger(isTrigger);

    std::shared_ptr<Collider> componentPtr = std::make_shared<Collider>(component);
    ge->AddComponent(componentPtr);
}

void LevelManager::AddRigidbody(std::shared_ptr<GameEntity> ge) {
    Rigidbody component = Rigidbody();
    component.SetGridSize(mGridSize);

    std::shared_ptr<Rigidbody> componentPtr = std::make_shared<Rigidbody>(component);
    ge->AddComponent(componentPtr);
}

void LevelManager::AddPlayerController(std::shared_ptr<GameEntity> ge) {
    PlayerController component = PlayerController();

    std::shared_ptr<PlayerController> componentPtr = std::make_shared<PlayerController>(component);
    ge->AddComponent(componentPtr);
}

void LevelManager::AddGhost(std::shared_ptr<GameEntity> ge, float awakeDelay, float scatterX, float scatterY) {
    Ghost component = Ghost();
    component.SetAwakeDelay(awakeDelay);

    std::shared_ptr<Ghost> componentPtr = std::make_shared<Ghost>(component);
    ge->AddComponent(componentPtr);
}
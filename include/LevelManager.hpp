#pragma once
#include <string>
#include <vector>
#include "Scene.hpp"
#include "TileType.hpp"

/**
 * Utility class for loading a PacMan Scene from a file.
*/
struct LevelManager {
    public:
        /**
         * Default constructor for the LevelManager.
        */
        LevelManager() {}
        /**
         * Constructs the LevelManager with the given grid size and renderer.
         * @param gridSize the size of one tile on the game grid, in pixels.
         * @param renderer a pointer to the renderer used by the Application.
        */
        LevelManager(float gridSize, SDL_Renderer* renderer);
        /**
         * Destructs the LevelManager.
        */
        ~LevelManager() {}
        /**
         * Loads a Scene from the text file at the given path.
         * @param fileName the name of the file to load, from the assets/levels/ directory.
         * @return the generated Scene.
        */
        Scene LoadLevelFile(std::string fileName);
    private:
        float mGridSize;
        int mCoinCount;
        int mPowerUpCoinCount;
        int mWallCount;
        int mPlayerCount;
        int mInkyCount;
        int mBlinkyCount;
        int mPinkyCount;
        int mClydeCount;
        int mGateCount;
        std::shared_ptr<GameEntity> mPlayerEntity;
        std::vector<std::shared_ptr<GameEntity>> mGhosts;
        std::vector<std::vector<bool>> mNavMesh;
        SDL_Renderer* mRenderer;
        Scene LoadSceneFromTileGrid(std::vector<std::vector<TileType>> tileGrid);
        void AddTileToScene(TileType tile, Scene& scene, float x, float y);
        std::shared_ptr<GameEntity> GenerateCoinTile(float x, float y);
        std::shared_ptr<GameEntity> GeneratePowerUpCoinTile(float x, float y);
        std::shared_ptr<GameEntity> GenerateWallTile(float x, float y);
        std::shared_ptr<GameEntity> GeneratePlayerTile(float x, float y);
        std::shared_ptr<GameEntity> GenerateGateTile(float x, float y);
        std::shared_ptr<GameEntity> GenerateInkyTile(float x, float y);
        std::shared_ptr<GameEntity> GenerateBlinkyTile(float x, float y);
        std::shared_ptr<GameEntity> GeneratePinkyTile(float x, float y);
        std::shared_ptr<GameEntity> GenerateClydeTile(float x, float y);
        std::shared_ptr<GameEntity> GenerateEntityAt(float x, float y);
        std::shared_ptr<GameEntity> GenerateGhostTemplate(float x, float y);
        void AddSpriteRenderer(std::shared_ptr<GameEntity> ge, const char* filePath, float size);
        void AddCollider(std::shared_ptr<GameEntity> ge, float size, bool isTrigger, 
            std::vector<std::string> ignoreTags);
        void AddCollider(std::shared_ptr<GameEntity> ge, float size, bool isTrigger);
        void AddRigidbody(std::shared_ptr<GameEntity> ge);
        void AddPlayerController(std::shared_ptr<GameEntity> ge);
        void AddGhost(std::shared_ptr<GameEntity> ge, float awakeDelay, float scatterX, float scatterY);
};
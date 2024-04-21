#pragma once
#include <string>
#include "GameApplication.hpp"
#include "LevelManager.hpp"

/**
 * Represents a GameApplication that runs a game of Pac Man.
*/
struct PacManGame : public GameApplication {
    public:
        /**
         * Constructs the PacManGame with the given window dimensions.
         * @param width the window width.
         * @param height the window height.
        */
        PacManGame(float width, float height);
        /**
         * Loads a Scene from the a text file.
         * @param file the name of the file to load.
        */
        void LoadLevelFile(std::string file);
        /**
         * Returns true if the win or loss conditions of Pac Man have been met.
         * @return whether win or loss conditions have been met.
        */
        bool QuitConditionMet() override;
    private:
        LevelManager mLevelManager;
        Scene GetSceneFromLevelFile(std::string filePath);
};
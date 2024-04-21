#pragma once
#include "Component.hpp"
#include <vector>

/**
 * A Component that handles all unique logic for the player in Pac Man.
*/
struct PlayerController : public Component {
    public:
        void Input(float deltaTime) override;
        void Update(float deltaTime) override;
        ComponentType GetType() override;
        /**
         * Sets the Ghosts that are present in the game scene.
         * @param ghosts the Ghosts in the scene.
        */
        void SetGhosts(std::vector<std::shared_ptr<GameEntity>> ghosts);
        /**
         * Sets the score that must be reached in order to win the game.
        */
        void SetWinScore(int winScore);
        /**
         * Returns true if the game is won. The game is won if all the coins in the scene are collected.
         * @return whether the game is won.
        */
        bool IsGameWon();
        /**
         * Returns true if the game is lost. The game is lost if the player touches a Ghost while they aren't
         * powered up.
         * @return whether the game is lost.
        */
        bool IsGameLost();
        void OnCollisionWithEntity(std::shared_ptr<GameEntity> other) override;
    private:
        std::vector<std::shared_ptr<GameEntity>> mGhosts;
        float mSpeed{10000};
        float mFrightenDuration{8};
        float mFrightenTimer{0};
        bool mPoweredUp{false};
        bool mGameOver{false};
        int mScore{0};
        int mWinScore{1};
};
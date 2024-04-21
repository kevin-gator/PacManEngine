#pragma once
#include <vector>
#include "Component.hpp"
#include "Direction.hpp"

/**
 * Represents the current state a Ghost is in.
*/
enum GhostState {
    Scatter,
    Chase,
    Frightened
};

/**
 * A Component that handles all unique logic for a Ghost in Pac Man.
*/
struct Ghost : public Component {
    public:
        /**
         * Sets the delay, in seconds, before this Ghost wakes up and starts moving after the game starts.
        */
        void SetAwakeDelay(float delay);
        void Update(float deltaTime) override;
        /**
         * Sets the player GameEntity of the game, which is used for pathfinding.
        */
        void SetPlayer(std::shared_ptr<GameEntity> player);
        /**
         * Sets a crude NavMesh for the Ghost, which is a 2D vector of booleans representing navigable tile
         * spaces in the level.
        */
        void SetNavMesh(std::vector<std::vector<bool>> navMesh, float gridSize);
        /**
         * Sets the target coordinates to move towards while this Ghost is in its Scatter state.
        */
        void SetScatterTarget(float x, float y);
        /**
         * Frightens this Ghost for the given duration, causing it to run away from the player.
        */
        void Frighten(float duration);
        ComponentType GetType() override;
    private:
        void SetTarget(float x, float y);
        const char* mPrevSpritePath;
        float mSpeed{7000};
        float mDefaultSpeed{7000};
        float mFrightenedSpeed{5000};
        void SetSprite(const char* filePath);
        void Move(float deltaTime);
        std::shared_ptr<GameEntity> mPlayer;
        std::vector<std::vector<bool>> mNavMesh;
        float mScatterTargetX;
        float mScatterTargetY;
        float mTargetX;
        float mTargetY;
        float mGridSize{32};
        float mTimer{0};
        float mFrightenedTimer{0};
        float mFrightenDuration{0};
        float mAwakeDelay;
        float mLastAISwitchTime{0};
        GhostState mState{Scatter};
        GhostState mLastUnfrightenedState;
        GhostState mPrevFrameState;
        Direction mDirection{Left};
};
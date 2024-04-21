#pragma once
#include "Component.hpp"
#include "Transform.hpp"

/**
 * A Component that handles basic physics for a GameEntity, such as correcting its position after a collision,
 * moving the Transform and teleporting the Transform to the opposite end of the screen when it moves to one
 * edge of the scene.
*/
struct Rigidbody : public Component {
    public:
        /**
         * Sets the grid size of the game, for use in snapping the Transform position to the grid when it is
         * close enough.
        */
        void SetGridSize(float gridSize);
        /**
         * Queues the given move for this frame.
         * @param x the X component of the move.
         * @param y the Y component of the move.
        */
        void QueueMove(float x, float y);
        /**
         * Performs the move that was queued this frame.
        */
        void PerformMove(float deltaTime);
        /**
         * Corrects collision for the Rigidbody.
         * @param thisTransform a shared pointer to the Transform of the GameEntity of this Rigidbody.
         * @param otherTransform a shared pointer to the Transform of the GameEntity that was collided with.
         * @param intersection a pointer to the SDL_FRect representing the overlap of the two Collider components.
        */
        void CorrectCollision(std::shared_ptr<Transform> thisTransform, 
            std::shared_ptr<Transform> otherTransform, SDL_FRect* intersection);
        ComponentType GetType() override;
    private:
        float mQueuedMoveX;
        float mQueuedMoveY;
        float mSceneWidth;
        float mSceneHeight;
        float mGridSize;
};
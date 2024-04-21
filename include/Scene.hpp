#pragma once
#include <string>
#include "GameEntity.hpp"
#include "Rigidbody.hpp"
#include "Collider.hpp"

/**
 * Represents a collection of GameEntities in a GameApplication.
*/
struct Scene {
    public:
        /**
         * Constructs the Scene.
        */
        Scene();
        /**
         * Destructs the Scene.
        */
        ~Scene();
        /**
         * Handles input for all GameEntities in this scene each frame.
         * @param deltaTime the time that has passed since the last frame, in seconds.
        */
        void Input(float deltaTime);
        /**
         * Performs updates to game logic, collision, and rigidbody physics for all GameEntities in this scene
         * each frame.
         * @param deltaTime the time that has passed since the last frame, in seconds.
        */
        void Update(float deltaTime);
        /**
         * Displays visual information for all GameEntities in this scene each frame.
         * @param renderer a pointer to the renderer that is used by the Application.
        */
        void Render(SDL_Renderer* renderer);
        /**
         * Adds a GameEntity to the Scene.
         * @param name the name to assign to the GameEntity.
         * @param gameEntity a shared pointer to the GameEntity to add.
        */
        void AddGameEntity(std::string name, std::shared_ptr<GameEntity> gameEntity);
        /**
         * Gets a pointer to a GameEntity in the Scene.
         * @param name the name of the GameEntity to retrieve.
         * @return a shared pointer to the GameEntity, or a null pointer if it isn't found.
        */
        std::shared_ptr<GameEntity> GetGameEntity(std::string name);
    private:
        void ProcessRigidbodies(float deltaTime);
        void ProcessRigidbodiesHelper(std::shared_ptr<GameEntity> gameEntity, 
            std::shared_ptr<std::vector<std::shared_ptr<Rigidbody>>> rigidbodies);
        void ProcessCollisions();
        void ProcessCollisionsHelper(std::shared_ptr<GameEntity> gameEntity, 
            std::shared_ptr<std::vector<std::shared_ptr<Collider>>> colliders);
        std::map<std::string, std::shared_ptr<GameEntity>> mGameEntities;
};
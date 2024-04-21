#pragma once
#include <map>
#include <memory>
#include <SDL3/SDL.h>

/**
 * Represents the types of Components that exist in the engine.
*/
enum ComponentType {
    NoComponent,
    TransformComponent,
    SpriteRendererComponent,
    ColliderComponent,
    RigidbodyComponent,
    PlayerControllerComponent,
    GhostComponent
};

struct GameEntity;

/**
 * Represents an object that can be attached to GameEntities to add behavior.
*/
struct Component {
    public:
        /**
         * Constructs the Component.
        */
        Component();
        /**
         * Destructs the Component.
        */
        virtual ~Component();
        /**
         * Handles input for the Component each frame.
         * @param deltaTime the time since the last frame, in seconds.
        */
        virtual void Input(float deltaTime);
        /**
         * Performs updates to game logic for the Component each frame.
         * @param deltaTime the time since the last frame, in seconds.
        */
        virtual void Update(float deltaTime);
        /**
         * Displays any visual information for the Component each frame.
         * @param renderer a pointer to the renderer that is used by the Application.
        */
        virtual void Render(SDL_Renderer* renderer);
        /**
         * Sets the enabled value of this Component to true.
        */
        void Enable();
        /**
         * Sets the enabled value of this Component to false.
        */
        void Disable();
        /**
         * Returns whether this Component is enabled.
         * @return the enabled value of this Component.
        */
        bool IsEnabled();
        /**
         * Sets the GameEntity that this Component is attached to.
         * @param gameEntity a shared pointer to the GameEntity.
        */
        void SetGameEntity(std::shared_ptr<GameEntity> gameEntity);
        /**
         * Returns the GameEntity this Component is attached to.
         * @return a shared pointer to the GameEntity.
        */
        std::shared_ptr<GameEntity> GetGameEntity();
        /**
         * Performs any operations needed for when the GameEntity of this Component collides with another GameEntity.
         * @param gameEntity a shared pointer to the GameEntity that was collided with.
        */
        virtual void OnCollisionWithEntity(std::shared_ptr<GameEntity> gameEntity) {}
        /**
         * Gets a pointer to a Component of type T that is attached to the GameEntity of this Component.
         * @tparam T the type of Component to search for.
         * @return a shared pointer to the Component, or a null pointer if no such Component can be found.
        */
        template <typename T>
        std::shared_ptr<T> GetNeighborComponent();
        /**
         * Gets the ComponentType of this Component.
         * @return the ComponentType.
        */
        virtual ComponentType GetType();
    protected:
        std::shared_ptr<GameEntity> mGameEntity; /**< A shared pointer to the GameEntity of this Component. */
    private:
        bool mEnabled{true};
};
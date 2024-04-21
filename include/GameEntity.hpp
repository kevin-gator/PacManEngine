#pragma once
#include <string>
#include <vector>
#include "Component.hpp"

/**
 * Represents an object in a Scene of a GameApplication that contains Components.
*/
struct GameEntity : public std::enable_shared_from_this<GameEntity>{
    public:
        /**
         * Constructs this GameEntity.
        */
        GameEntity();
        /**
         * Destructs this GameEntity.
        */
        virtual ~GameEntity();
        /**
         * Handles input for all enabled Components of this GameEntity each frame.
         * @param deltaTime the time that has passed since the last frame, in seconds.
        */
        virtual void Input(float deltaTime);
        /**
         * Performs updates to game logic for all enabled Components of this GameEntity each frame.
         * @param deltaTime the time that has passed since the last frame, in seconds.
        */
        virtual void Update(float deltaTime);
        /**
         * Displays any visual information for all enabled Components of this GameEntity each frame.
         * @param renderer a pointer to the renderer that is used by the Application.
        */
        virtual void Render(SDL_Renderer* renderer);
        /**
         * Adds a Component of type T to this GameEntity.
         * @tparam T the type of Component to add.
         * @param c a shared pointer to the Component to add.
        */
        template <typename T>
        void AddComponent(std::shared_ptr<T> c) {
            mComponents[c->GetType()]= c;
            std::shared_ptr<GameEntity> thisPtr = shared_from_this();
            c->SetGameEntity(thisPtr);
        }
        /**
         * Gets a Component of the given type from this GameEntity.
         * @tparam T the type of Component to get.
         * @param type the ComponentType to get.
         * @return a shared pointer to the Component, or a null pointer if it isn't found.
        */
        template <typename T>
        std::shared_ptr<T> GetComponent(ComponentType type) {
            auto found = mComponents.find(type);
            if(found != mComponents.end()){
                return dynamic_pointer_cast<T>(found->second);
            }
            return nullptr;
        }
        /**
         * Adds the given GameEntity as a child of this GameEntity.
         * @param name the name to assign to the child.
         * @param child the child GameEntity to add.
        */
        void AddChildEntity(std::string name, std::shared_ptr<GameEntity> child);
        /**
         * Gets a child GameEntity with the given name.
         * @return a shared pointer to the child, or a null pointer if it can't be found.
        */
        std::shared_ptr<GameEntity> GetChildEntity(std::string name);
        /**
         * Gets the children of this GameEntity.
         * @return the String->GameEntity map of child GameEntities for this GameEntity.
        */
        std::map<std::string, std::shared_ptr<GameEntity>> GetChildren();
        /**
         * Enables this GameEntity, allowing it to perform its Input, Update, and Render methods.
        */
        void Enable();
        /**
         * Disables this GameEntity, preventing it from performing its Input, Update, and Render methods.
        */
        void Disable();
        /**
         * Returns whether this GameEntity is enabled.
         * @return whether this GameEntity is enabled or not.
        */
        bool IsEnabled();
        /**
         * Performs any operations needed for when this GameEntity collides with another GameEntity.
         * @param gameEntity a shared pointer to the GameEntity that was collided with.
        */
        void OnCollisionWithEntity(std::shared_ptr<GameEntity> gameEntity);
        /**
         * Adds the given tag to this GameEntity.
         * @param tag the tag to add.
        */
        void AddTag(std::string tag);
        /**
         * Returns whether this GameEntity has the given tag.
         * @param tag the tag to check for.
         * @return whether this GameEntity has the tag.
        */
        bool HasTag(std::string tag);
    private:
        std::vector<std::string> mTags;
        bool mEnabled{true};
        std::map<ComponentType, std::shared_ptr<Component>> mComponents;
        std::map<std::string, std::shared_ptr<GameEntity>> mChildEntities;
};
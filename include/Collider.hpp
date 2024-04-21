#pragma once
#include "Component.hpp"
#include <vector>

/**
 * A Component that handles collision itself and other Colliders.
*/
struct Collider : public Component {
    public:
        void Update(float deltaTime) override;
        ComponentType GetType() override;
        /**
         * Resizes the Collider rectangle to the given dimensions.
         * @param width the width to resize to.
         * @param height the height to resize to.
        */
        void ResizeCollider(float width, float height);
        /**
         * Returns the Collider's rectangle.
         * @return the Collider's rectangle.
        */
        SDL_FRect GetRectangle();
        /**
         * Sets the "is trigger" flag of this Collider. If a Collider is a trigger, it will still
         * invoke collision methods, but it will not stop Rigidbody movement.
         * @param isTrigger the value to set for the "is trigger" flag.
        */
        void SetIsTrigger(bool isTrigger);
        /**
         * Adds the given tag to this Collider's list of tags to ignore. The Collider won't process
         * Collision with GameEntities that have these tags.
         * @param tag the tag to ignore.
        */
        void AddIgnoreTag(std::string tag);
        /**
         * Returns whether this Collider is a trigger.
         * @return whether this is a trigger.
        */
        bool IsTrigger();
        /**
         * Returns true if this Collider is currently colliding with the given one.
         * @param other a shared pointer to the other Collider.
         * @return whether a collision is detected.
        */
        bool CollidesWith(std::shared_ptr<Collider> other);
        /**
         * Processes logic for when this Collider collides with another one.
         * @param other a shared pointer to the other Collider.
        */
        void OnCollisionWith(std::shared_ptr<Collider> other);
    private:
        std::vector<std::string> mIgnoreTags;
        bool mIsTrigger{false};
        SDL_FRect mRectangle{0.0, 0.0, 32.0, 32.0};
};
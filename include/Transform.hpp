#pragma once
#include "Component.hpp"

/**
 * A Component that controls the position in world space of a GameEntity.
*/
struct Transform : public Component {
    public:
        /**
         * Sets the position of the Transform.
         * @param x the X coordinate to set.
         * @param y the Y coordinate to set.
        */
        void SetPosition(float x, float y);
        /**
         * Moves the position of the Transform by the given amounts.
         * @param x the X coordinate to add.
         * @param y the Y coordinate to add.
        */
        void Move(float x, float y);
        /**
         * Gets the X coordinate of the Transform.
         * @return the X coordinate of the Transform.
        */
        float GetX();
        /**
         * Gets the Y coordinate of the Transform.
         * @return the Y coordinate of the Transform.
        */
        float GetY();
        /**
         * Sets the value for the "constrain children" flag of this Transform (defaults to false). If the
         * value is true, child GameEntities of this Transform's GameEntity will move with it.
        */
        void SetConstrainChildren(bool value);
        ComponentType GetType() override;
    private:
        bool mConstrainChildren{false};
        float mX;
        float mY;
};
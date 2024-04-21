#pragma once
#include "Application.hpp"

/**
 * Represents an Application that displays Scenes.
*/
struct GameApplication : public Application {
    public:
        /**
         * Constructs the GameApplication with the given width and height.
         * @param width the width of the Application window.
         * @param height the height of the Application window.
        */
        GameApplication(float width, float height);
        /**
         * Loads the given Scene in this GameApplication.
         * @param scene the Scene to load.
        */
        void LoadScene(Scene scene);
    protected:
        /**
         * Handles input for the current Scene each frame.
         * @param deltaTime the time since the last frame, in seconds.
        */
        void Input(float deltaTime) override;
        /**
         * Updates game logic for the current Scene each frame.
         * @param deltaTime the time since the last frame, in seconds.
        */
        void Update(float deltaTime) override;
        /**
         * Displays visual information for the current Scene each frame.
        */
        void Render() override;
        std::shared_ptr<Scene> mScene; /**< A shared pointer to the current Scene. */
};
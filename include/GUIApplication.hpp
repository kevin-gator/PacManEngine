#pragma once
#include "Application.hpp"

/**
 * Represents an Application with support for basic GUI operations like rendering images and processing key
 * press events.
*/
struct GUIApplication : public Application {
    public:
        /**
         * Constructs a GUIApplication with the given window dimensions.
         * @param width the width of the window.
         * @param height the height of the window.
        */
        GUIApplication(float width, float height);
    protected:
        void Input(float deltaTime) override;
        /**
         * A method called inside the Input method for handling keyboard inputs.
        */
        virtual void HandleKeyboardInputs(float deltaTime) {};
        /**
         * Renders an image in the window.
         * @param filePath the file path of the image to load.
         * @param x the x coordinate of the Rect to project the image on.
         * @param y the y coordinate of the Rect to project the image on.
         * @param w the width of the Rect to project the image on.
         * @param h the height of the Rect to project the image on.
        */
        void RenderImage(const char* filePath, float x, float y, float w, float h);
        /**
         * Returns true if the client started pressing the given key this frame.
         * @param key the key to check.
        */
        bool KeyPressStart(SDL_Scancode key);
    private:
        const Uint8* mCurrKeyboardState;
        Uint8 mPrevKeyboardState[SDL_NUM_SCANCODES];
};
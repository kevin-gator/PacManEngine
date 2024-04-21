#pragma once
#include <SDL3/SDL.h>
#include "Scene.hpp"

/**
 * Represents an SDL-based application with a single window.
*/
struct Application {
    public:
        /**
         * Constructs an Application with the given window width and height.
         * @param width the window width.
         * @param height the window height.
        */
        Application(float width, float height);
        /**
         * Destroys the Application, shutting it down.
        */
        virtual ~Application();
        /**
         * Performs the run loop for the Application to run at the given FPS.
         * @param the target FPS to run the Application at.
        */
        void Run(float targetFPS);
        /**
         * Checks whether any special conditions have been met to quit this Application (other than when the client closes 
         * the window, which will always quit the Application). When this method returns true, the Application will shut down.
         * By default, this will always return false.
         * @return whether any quit conditions have been met.
        */
        virtual bool QuitConditionMet();
    protected:
        /**
         * Handles input for the Application each frame.
         * @param deltaTime the time that has passed since the last frame, in seconds.
        */
        virtual void Input(float deltaTime) = 0;
        /**
         * Performs updates to logic for the Application each frame.
         * @param deltaTime the time that has passed since the last frame, in seconds.
        */
        virtual void Update(float deltaTime) = 0;
        /**
         * Displays any visual information for the Application each frame.
        */
        virtual void Render() = 0;
        /**
         * Renders an image in the window.
         * @param filePath the file path of the image to load.
         * @param x the x coordinate of the Rect to project the image on.
         * @param y the y coordinate of the Rect to project the image on.
         * @param w the width of the Rect to project the image on.
         * @param h the height of the Rect to project the image on.
        */
        //void RenderImage(const char* filePath, float x, float y, float w, float h);
        bool mRun{true}; /**< Whether the Application is running. */
        float mWidth; /**< The width of the Application window. */
        float mHeight; /**< The height of the Application window. */
        SDL_Renderer* mRenderer; /**< A pointer to the SDL Renderer of this Application. */
    private:
        void StartUp(float width, float height);
        void ShutDown();
        SDL_Window* mWindow;
};
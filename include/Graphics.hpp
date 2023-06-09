/*
Singleton class for handling graphics, rendering, windowing
Not frame limited, no DeltaTime yet
*/
#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "Input.hpp"

class Graphics
{
public:
    /// @brief Get the single shared instance
    static Graphics *GetInstance();
    /// @brief Deletes the shared instance, and cleans up after itself
    static void Release();

    /// @brief Creates the actual window, needed for proper use of the class
    /// @param title Windows name
    /// @param width Width of window in pixels
    /// @param height Height of window in pixels
    void CreateWindow(const char *title, unsigned int width, unsigned int height);

    /// @brief Draw a point to the screen
    /// @param x
    /// @param y
    /// @param color RGBA value to draw
    void DrawPoint(unsigned int x, unsigned int y, SDL_Color color);

    /// @brief Draw a SDL_Texture to the screen
    /// @param texture 
    void DrawTexture(SDL_Texture* texture);

    /// @brief Create a SDL_Texture from a SDL_Surface
    /// @param surface 
    SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

    /// @brief Update the window, input, clear screen
    /// @return Returns if the window should close or not
    bool Update();

    /// @brief Switch buffers. Nothing more than SDL_Present
    void Render();

    /// @brief Manually close the window and application
    void CloseWindow() { windowShouldClose = true; }

    // Goal: Make it so this is never needed
    SDL_Renderer *GetRenderer() { return renderer; }

    unsigned int width{};
    unsigned int height{};

    Graphics(Graphics &other) = delete;
    void operator=(const Graphics &) = delete;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    // All window events
    SDL_Event events;
    bool windowShouldClose = false;

    Graphics()
    {
        // Initialize SDL 
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    }

    ~Graphics()
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;

        SDL_DestroyWindow(window);
        window = nullptr;

        SDL_Quit();
    }

    static Graphics *instance_;
};
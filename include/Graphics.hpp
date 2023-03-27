#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class Graphics
{
public:
    static Graphics* GetInstance();
    static void Release();

    Graphics(Graphics &other) = delete;
    void operator=(const Graphics &) = delete;

    void CreateWindow(const char* title, unsigned int width, unsigned int height);
    void DrawPoint(unsigned int x, unsigned int y, SDL_Color color);
    bool Update();
    void Render();

    void CloseWindow() {windowShouldClose = true;}
    SDL_Renderer* GetRenderer() {return renderer;}

    unsigned int width{};
    unsigned int height{};

    const Uint8* keyboardState;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;    

    SDL_Event events;
    bool windowShouldClose = false;

    Graphics()
    {
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

    static Graphics* instance_;
};
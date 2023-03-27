#include "Graphics.hpp"

Graphics* Graphics::instance_ = nullptr;

Graphics* Graphics::GetInstance()
{
    if(instance_ == nullptr)
        instance_ = new Graphics();
    return instance_;
}

void Graphics::Release()
{
    delete instance_;
}

bool Graphics::Update()
{
    // Polls all the events, ensures all are gotten
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            CloseWindow();
            break;
        
        default:
            break;
        }
    }

    // Update input
    keyboardState = SDL_GetKeyboardState(nullptr);

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    return windowShouldClose;
}

void Graphics::CreateWindow(const char *title, unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Graphics::DrawPoint(unsigned int x, unsigned int y, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, x, y);
}

void Graphics::Render()
{
    SDL_RenderPresent(renderer);
}

bool Graphics::GetKeyDown(SDL_Scancode key)
{
    return keyboardState[key];
}

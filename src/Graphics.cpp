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

    keyboardState = SDL_GetKeyboardState(nullptr);
    
    return windowShouldClose;
}

void Graphics::CreateWindow(const char *title, unsigned int width, unsigned int height)
{
    this->width = width; this->height = height;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
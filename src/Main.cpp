#include <iostream>

#include "Graphics.hpp"
#include "Mandelbrot.hpp"

int main()
{
    Graphics *window = Graphics::GetInstance();
    window->CreateWindow("Hello World", 800, 800);

    Mandelbrot mandelbrot({-0.5, 0.0}, 0.7, 30);

    while (!window->Update())
    {
        if (window->keyboardState[SDL_SCANCODE_ESCAPE])
            window->CloseWindow();

        mandelbrot.Render();

        window->Render();
    }

    window->Release();

    return 0;
}
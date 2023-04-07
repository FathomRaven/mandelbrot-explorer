#include <iostream>

#include "Graphics.hpp"
#include "Mandelbrot.hpp"

int main()
{
    Graphics *window = Graphics::GetInstance();
    window->CreateWindow("Hello World", 800, 800);

    Mandelbrot mandelbrot({-0.5, 0.0}, 0.7, 30, window->width, window->height);

    while (!window->Update())
    {   
        mandelbrot.Update();
        mandelbrot.Render();
        
        window->Render();
    }

    window->Release();
    window = nullptr;

    return 0;
}
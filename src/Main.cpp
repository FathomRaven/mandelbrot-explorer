#include <iostream>

#include "Graphics.hpp"
#include "Mandelbrot.hpp"

int main()
{
    Graphics *window = Graphics::GetInstance();
    window->CreateWindow("Mandelbrot Explorer", 800, 800);

    Mandelbrot mandelbrot({-0.6, 0.0}, 0.7, 200, window->width, window->height, 10);

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
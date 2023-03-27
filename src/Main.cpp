#include <iostream>
#include "Graphics.hpp"

int main()
{
    Graphics* window = Graphics::GetInstance();
    window->CreateWindow("Hello World", 800, 800);

    while (!window->Update())
    {
        if(window->keyboardState[SDL_SCANCODE_ESCAPE])
            window->CloseWindow();

        window->DrawPoint(0, 0, {255, 0, 0, 255});

        window->Render();
    }

    window->Release();

    return 0;
}
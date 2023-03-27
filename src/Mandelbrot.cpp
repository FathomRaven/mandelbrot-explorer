#include "Mandelbrot.hpp"

Mandelbrot::Mandelbrot(std::complex<double> center, double zoom, unsigned int maxIterations)
    : center(center), zoom(zoom), maxIterations(maxIterations)
{
    graphicsInstance = Graphics::GetInstance();
}

Mandelbrot::~Mandelbrot()
{
    graphicsInstance = nullptr;
}

void Mandelbrot::Render()
{
    // Loop through every pixel on the screen
    for (unsigned int x = 0; x < graphicsInstance->width; x++)
    {
        for (unsigned int y = 0; y < graphicsInstance->height; y++)
        {
            // Get the variable c from the zoom, screen width and height, and current pixel
            const std::complex<double> c(center.real() + (x - 0.5 * graphicsInstance->width) / (0.5 * zoom * graphicsInstance->width),
                                         center.imag() + (y - 0.5 * graphicsInstance->height) / (0.5 * zoom * graphicsInstance->height));

            // The position
            std::complex<double> z = 0;
            // Number of iterations
            unsigned int count = 0;

            while (abs(z) < 2.0 && count < maxIterations)
            {
                // Where the magic happens
                // Z = Z^2 + C
                z = z * z + c;
                count++;
            }

            // If the point is deemed in the set, draw as black
            if (count == maxIterations)
            {
                graphicsInstance->DrawPoint(x, y, {0, 0, 0, 255});
                continue;
            }

            // Otherwise, draw using count
            unsigned char r = count * 5;
            unsigned char g = count * 5;
            unsigned char b = count * 5;

            graphicsInstance->DrawPoint(x, y, {r, g, b, 255});
        }
    }
}

void Mandelbrot::Update()
{
    // Everything here takes zoom into account, seems to help movement and zooming still work as depth increases 

    if(graphicsInstance->GetKeyDown(SDL_SCANCODE_SPACE))
        zoom += zoom / 10;
    if(graphicsInstance->GetKeyDown(SDL_SCANCODE_LCTRL))
        zoom -= zoom / 10;

    if(graphicsInstance->GetKeyDown(SDL_SCANCODE_LEFT))
        center.real(std::real(center) - 0.1 / zoom);
    if(graphicsInstance->GetKeyDown(SDL_SCANCODE_RIGHT))
        center.real(std::real(center) + 0.1 / zoom);    
    if(graphicsInstance->GetKeyDown(SDL_SCANCODE_UP))
        center.imag(std::imag(center) - 0.1 / zoom);
    if(graphicsInstance->GetKeyDown(SDL_SCANCODE_DOWN))
        center.imag(std::imag(center) + 0.1 / zoom);    
}

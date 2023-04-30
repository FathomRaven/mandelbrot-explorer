#include "Mandelbrot.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

Mandelbrot::Mandelbrot(std::complex<double> center, double zoom, unsigned int maxIterations, unsigned int width, unsigned int height, unsigned int threadCount)
    : center(center), zoom(zoom), maxIterations(maxIterations), width(width), height(height), threadCount(threadCount)
{
    graphicsInstance = Graphics::GetInstance();

    defaultCenter = center;
    defaultZoom = zoom;

    defaultWidth = width;
    defaultHeight = height;

    // Create the new surface. Messy
    // For some reason, this format makes the CreateTextureFromSurface function faster. No, I do not know why, and I probably never will
    renderingSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    // Cast the pixels from void* to Uint32*, so they can be changed
    pixels = static_cast<Uint32*>(renderingSurface->pixels);
}

Mandelbrot::~Mandelbrot()
{
    graphicsInstance = nullptr;

    SDL_FreeSurface(renderingSurface);
    pixels = nullptr;
    SDL_DestroyTexture(renderingTexture);
}

void Mandelbrot::Render()
{
    // If the variables, center or zoom, have been updated, then recalculate the set
    if(updateSet)
    {
        CalculateSet();
    }

    // Draw to screen
    graphicsInstance->DrawTexture(renderingTexture);
}

void Mandelbrot::CalculateSet()
{
    std::thread* threads[threadCount];

    for (size_t i = 0; i < threadCount; i++)
    {
        threads[i] = new std::thread(&Mandelbrot::CalculateSectionOfSet, this, width / threadCount, (width / threadCount) * i);
    }
    
    for (auto &&thread : threads)
    {
        thread->join();
        delete thread;
    }

    /*
    You might think, "Hey, why not just make a texture, and then use the SDL_Lock and Unlock functions?
    Why make a surface just to make a texture?"
    The answer is, for some reason, apparently, this is faster. Locking and unlocking is miserably slow from my tests.
    Until I have a better option, this will just have to do
    */
    renderingTexture = graphicsInstance->CreateTextureFromSurface(renderingSurface);

    updateSet = false;
}

void Mandelbrot::CalculateSectionOfSet(unsigned int sectionWidth, unsigned int sectionOffset)
{
    // Loop through every pixel on the screen
    for (unsigned int x = sectionOffset; x < sectionWidth + sectionOffset; x++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            // Get the variable c from the zoom, screen width and height, and current pixel
            const std::complex<double> c(center.real() + (x - 0.5 * width) / (0.5 * zoom * width),
                                         center.imag() + (y - 0.5 * height) / (0.5 * zoom * height));

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
                pixels[x + (width * y)] = 0 + (255 << 24);
                continue;
            }

            // Otherwise, draw using count
            unsigned char r = count * 5;
            unsigned char g = count * 5;
            unsigned char b = count * 5;

            /*
            Pixels is a 2D array
            Bit shifts the colors to match the RGBA32 format
            */
            pixels[x + (width * y)] = (r) + (g << 8) + (b << 16) + (255 << 24);
        }
    }

    pthread_exit(NULL);
}

void Mandelbrot::Update()
{

    // ZOOM

    if(Input::GetKeyDown(SDL_SCANCODE_SPACE))
    {
        zoom += zoom / 10;
        updateSet = true;
    }
    if(Input::GetKeyDown(SDL_SCANCODE_LCTRL))
    {
        zoom -= zoom / 10;
        updateSet = true;
    }

    // MOVING

    if(Input::GetKeyDown(SDL_SCANCODE_LEFT))
    {
        center.real(std::real(center) - 0.1 / zoom);
        updateSet = true;
    }

    if(Input::GetKeyDown(SDL_SCANCODE_RIGHT))
    {
        center.real(std::real(center) + 0.1 / zoom);    
        updateSet = true;
    }

    if(Input::GetKeyDown(SDL_SCANCODE_UP))
    {
        center.imag(std::imag(center) - 0.1 / zoom);
        updateSet = true;
    }

    if(Input::GetKeyDown(SDL_SCANCODE_DOWN))
    {
        center.imag(std::imag(center) + 0.1 / zoom);    
        updateSet = true;
    }

    // RESET

    if(Input::GetKeyPressed(SDL_SCANCODE_R))
    {
        center = defaultCenter;
        zoom = defaultZoom;
        updateSet = true;
    }

    // SCREENSHOT

    if(Input::GetKeyPressed(SDL_SCANCODE_S))
    {
        // Output folder
        std::string filename{"pictures/"};

        // Gets the zoom, x, and y coords, and strings them together
        filename.append(std::to_string(zoom));
        filename += " ";
        filename.append(std::to_string(center.real()));
        filename += " ";
        filename.append(std::to_string(center.imag()));

        // Use stbi to write as an image
        stbi_write_png(filename.append(".png").c_str(), width, height, 4, renderingSurface->pixels, width * 4);
    }

    // CHANGE ITERATIONS

    if(Input::GetKeyPressed(SDL_SCANCODE_LEFTBRACKET))
    {
        maxIterations = maxIterations / 2;
        updateSet = true;
    }

    if(Input::GetKeyPressed(SDL_SCANCODE_RIGHTBRACKET))
    {
        if(maxIterations == 0)
            maxIterations = 1;

        maxIterations = maxIterations * 2;
        updateSet = true;
    }

    // PRINT INFO

    if(Input::GetKeyPressed(SDL_SCANCODE_I))
    {
        std::cout << "Current stats" << '\n';
        std::cout << "------------------------------------" << '\n';
        std::cout << "Iteration count: " << maxIterations << '\n';
        std::cout << "Zoom: " << zoom << '\n';
        std::cout << "X: " << center.real() << '\n';
        std::cout << "Y: " << center.imag() << '\n';
        std::cout << '\n';
    }
}
/*
Mandelbrot class
Calculates the mandelbrot set and renders it to the screen
*/

#pragma once

#include <complex>
#include "Graphics.hpp"

class Mandelbrot
{
public:
    /// @param center Initial offset
    /// @param zoom Starting value of zoom
    /// @param maxIterations Max amount of iterations
    Mandelbrot(std::complex<double> center, double zoom, unsigned int maxIterations, unsigned int width, unsigned int height);
    ~Mandelbrot();

    /// @brief Draw to the screen
    void Render();

    /// @brief Calculate the set, and update the pixels
    void CalculateSet();

    /// @brief Handle input before rendering
    void Update();

private:
    Graphics *graphicsInstance;

    std::complex<double> center;
    double zoom;
    unsigned int maxIterations;

    unsigned int width;
    unsigned int height;

    // Should the set be recalculated?
    bool updateSet{true};

    // The surface that is manipulated. Faster than using a texture (???)
    SDL_Surface* renderingSurface{nullptr};
    
    // Texture created from surface, to be drawn to the screen
    SDL_Texture* renderingTexture{nullptr};

    // The actual pixels in 32 bit unsigned integers
    Uint32* pixels{nullptr};
};
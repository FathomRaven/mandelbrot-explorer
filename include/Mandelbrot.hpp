/*
Mandelbrot class
Calculates the mandelbrot set and renders it to the screen
*/

#pragma once

#include <complex>
#include <thread>
#include "Graphics.hpp"

class Mandelbrot
{
public:
    /// @param center Initial offset
    /// @param zoom Starting value of zoom
    /// @param maxIterations Max amount of iterations
    Mandelbrot(std::complex<double> center, double zoom, unsigned int maxIterations, unsigned int width, unsigned int height, unsigned int threadCount);
    ~Mandelbrot();

    /// @brief Draw to the screen
    void Render();

    /// @brief Handle input before rendering
    void Update();

private:
    Graphics *graphicsInstance;

    /// @brief Calculate the set, and update the pixels
    void CalculateSet();

    /// @brief Thread function for calculating sections of the overall set 
    void CalculateSectionOfSet(unsigned int sectionWidth, unsigned int sectionOffset);

    std::complex<double> center;
    double zoom;
    unsigned int maxIterations;

    unsigned int width;
    unsigned int height;

    unsigned int threadCount;

    // Should the set be recalculated?
    bool updateSet{true};

    // The surface that is manipulated. Faster than using a texture (???)
    SDL_Surface* renderingSurface{nullptr};
    
    // Texture created from surface, to be drawn to the screen
    SDL_Texture* renderingTexture{nullptr};

    // The actual pixels in 32 bit unsigned integers
    Uint32* pixels{nullptr};
};
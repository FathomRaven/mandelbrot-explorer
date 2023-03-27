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
    Mandelbrot(std::complex<double> center, double zoom, unsigned int maxIterations);
    ~Mandelbrot();

    /// @brief Draw the mandelbrot set to the screen
    void Render();

    /// @brief Handle input before rendering
    void Update();

private:
    Graphics *graphicsInstance;

    std::complex<double> center;
    double zoom;
    unsigned int maxIterations;
};
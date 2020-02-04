#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer() :
    window(nullptr),
    renderer(nullptr)
{
    window = SDL_CreateWindow(
        "StrategyGameJam",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window) throw std::runtime_error("Failed to create SDL window!");
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) throw std::runtime_error("Failed to create SDL renderer!");
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::draw()
{
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

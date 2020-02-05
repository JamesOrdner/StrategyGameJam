#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer() :
    zoom(1.f),
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
    
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::clear() const
{
    SDL_RenderClear(renderer);
}

void Renderer::draw(SDL_Texture* texture, SDL_Rect dest, double rotation) const
{
    dest.w *= 1.f / zoom;
    dest.h *= 1.f / zoom;
    dest.x += (dest.x - screenWidth / 2) * (1.f / zoom);
    dest.y += (dest.y - screenHeight / 2) * (1.f / zoom);
    SDL_RenderCopyEx(
        renderer,
        texture,
        nullptr,
        &dest,
        rotation,
        nullptr,
        SDL_FLIP_NONE);
}

void Renderer::present() const
{
    SDL_RenderPresent(renderer);
}


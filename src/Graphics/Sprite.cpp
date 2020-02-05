#include "Sprite.hpp"
#include <SDL_render.h>

Sprite::Sprite(SDL_Renderer* renderer, const SDL_Rect& size, Uint32 color)
{
    bounds = size;
    bounds.x = -bounds.w / 2;
    bounds.y = -bounds.h / 2;
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, size.w, size.h, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(surface, nullptr, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}

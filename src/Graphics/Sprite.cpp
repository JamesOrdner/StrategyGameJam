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

Sprite::Sprite(const std::string& filepath) :
    texture(nullptr),
    filepath(filepath)
{
    auto* surf = SDL_LoadBMP(filepath.c_str());
    if (!surf) throw std::runtime_error("Invalid texture path: " + filepath);
    bounds.w = surf->w;
    bounds.h = surf->h;
    bounds.x = -bounds.w / 2;
    bounds.y = -bounds.h / 2;
    SDL_FreeSurface(surf);
}

Sprite::~Sprite()
{
    if (texture) SDL_DestroyTexture(texture);
}

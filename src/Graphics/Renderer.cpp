#include "Renderer.hpp"
#include "../UI/UIObject.hpp"
#include <SDL_hints.h>
#include <iostream>

Renderer::Renderer() :
    zoom(1.f),
    cameraOffset{},
    window(nullptr),
    renderer(nullptr)
{
    window = SDL_CreateWindow(
        "StrategyGameJam",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1280, 720,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window) throw std::runtime_error("Failed to create SDL window!");
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) throw std::runtime_error("Failed to create SDL renderer!");
    
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    
    hidpiMult = static_cast<float>(screenWidth) / windowWidth;
}

Renderer::~Renderer()
{
    for (auto& texture : textureAssets) {
        SDL_DestroyTexture(texture.second);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::clear() const
{
    SDL_RenderClear(renderer);
}

void Renderer::draw(SDL_Texture* texture, SDL_Rect dest, double rotation) const
{
    float adjustedZoom = zoom * hidpiMult;
    
    dest.x += screenWidth / 2 - cameraOffset.x;
    dest.y += screenHeight / 2 + cameraOffset.y;
    dest.x += (dest.x - screenWidth / 2.f) * adjustedZoom - (dest.x - screenWidth / 2.f);
    dest.y += (dest.y - screenHeight / 2.f) * adjustedZoom - (dest.y - screenHeight / 2.f);
    
    dest.w *= adjustedZoom;
    dest.h *= adjustedZoom;
    
    SDL_RenderCopyEx(
        renderer,
        texture,
        nullptr,
        &dest,
        rotation,
        nullptr,
        SDL_FLIP_NONE);
}

void Renderer::drawUI(const UIObject* rootObject)
{
    SDL_Rect screenBounds{ .x = 0, .y = 0, .w = windowWidth, .h = windowHeight };
    for (const auto& object : rootObject->subobjects) {
        drawUI(object, screenBounds);
    }
}

void Renderer::drawUI(const UIObject& object, const SDL_Rect& parentBoundsAbs)
{
    SDL_Rect dest = object.bounds;
    // TODO: implement anchor offset
    
    SDL_RenderCopyEx(
        renderer,
        texture(object.textureFilepath),
        nullptr,
        &dest,
        object.rotation,
        nullptr,
        SDL_FLIP_NONE);
    
    for (const auto& subobject : object.subobjects) {
        drawUI(subobject, dest);
    }
}

void Renderer::present() const
{
    SDL_RenderPresent(renderer);
}

SDL_Texture* Renderer::texture(const std::string& filepath)
{
    auto it = textureAssets.find(filepath);
    if (it == textureAssets.end()) {
        auto* surf = SDL_LoadBMP(filepath.c_str());
        auto* tex = textureAssets[filepath] = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
        return tex;
    }
    else {
        return it->second;
    }
}

SDL_Point Renderer::screenToWorldCoords(const SDL_Point& point) const
{
    SDL_Point worldCoords = point;
    worldCoords.x -= windowWidth / 2;
    worldCoords.y -= windowHeight / 2;
    worldCoords.x /= zoom;
    worldCoords.y /= zoom;
    worldCoords.x += cameraOffset.x;
    worldCoords.y -= cameraOffset.y;
    worldCoords.y *= -1;
    
    return worldCoords;
}

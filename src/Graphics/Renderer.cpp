#include "Renderer.hpp"
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
    
    TTF_Init();
    font = TTF_OpenFont("res/fonts/Capture_it.ttf", 64 * screenWidth / windowWidth);
    if (!font) throw std::runtime_error("Failed to open font!");
}

Renderer::~Renderer()
{
    for (const auto& texMapPair : textureAssets) {
        SDL_DestroyTexture(texMapPair.second.texture);
    }
    
    TTF_CloseFont(font);
    TTF_Quit();
    
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

void Renderer::draw(const std::string& filepath, const SDL_Point& position, double rotation)
{
    const auto& asset = texture(filepath);
    SDL_Rect dest = asset.bounds;
    dest.x += position.x;
    dest.y -= position.y;
    draw(asset.texture, dest, rotation);
}

void Renderer::drawSurface(SDL_Surface* surface, const SDL_Point& point, UIAnchor anchor)
{
    auto* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest{ point.x, point.y, surface->w, surface->h };
    SDL_RenderCopyEx(
        renderer,
        texture,
        nullptr,
        &dest,
        0,
        nullptr,
        SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
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
    if (object.bHidden) return;
    
    if (object.anchor == UIAnchor::World) {
        draw(object.textureFilepath, { object.bounds.x, object.bounds.y }, 0);
    }
    else {
        SDL_Rect dest = object.bounds;
        // TODO: implement anchor offset
        
        if (!object.textureFilepath.empty()) {
            SDL_RenderCopyEx(
                renderer,
                texture(object.textureFilepath).texture,
                nullptr,
                &dest,
                object.rotation,
                nullptr,
                SDL_FLIP_NONE);
        }
        
        
        if (!object.text.empty()) {
            auto* textSurface = TTF_RenderText_Solid(font, object.text.c_str(), { 255, 255, 255, 255 });
            drawSurface(textSurface, { object.bounds.x, object.bounds.y }, UIAnchor::TopLeft);
            SDL_FreeSurface(textSurface);
        }
        
        for (const auto& subobject : object.subobjects) {
            drawUI(subobject, dest);
        }
    }
}

void Renderer::present() const
{
    SDL_RenderPresent(renderer);
}

const Renderer::TextureAsset& Renderer::texture(const std::string& filepath)
{
    auto it = textureAssets.find(filepath);
    if (it == textureAssets.end()) {
        TextureAsset asset;
        auto* surf = SDL_LoadBMP(filepath.c_str());
        if (!surf) throw std::runtime_error("Invalid texture path: " + filepath);
        asset.texture = SDL_CreateTextureFromSurface(renderer, surf);
        asset.bounds.w = surf->w;
        asset.bounds.h = surf->h;
        asset.bounds.x = -asset.bounds.w / 2;
        asset.bounds.y = -asset.bounds.h / 2;
        SDL_FreeSurface(surf);
        return textureAssets[filepath] = asset;
    }
    else {
        return it->second;
    }
}

SDL_Surface* Renderer::genTextTexture(const std::string& text, SDL_Color color)
{
    return TTF_RenderText_Solid(font, text.c_str(), color);
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

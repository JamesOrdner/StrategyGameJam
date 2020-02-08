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
        640, 480,
        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN_DESKTOP
    );
    if (!window) throw std::runtime_error("Failed to create SDL window!");
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) throw std::runtime_error("Failed to create SDL renderer!");
    
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    
    hidpiMult = static_cast<float>(screenWidth) / windowWidth;
    
    TTF_Init();
    font = TTF_OpenFont("res/fonts/Capture_it.ttf", 128);
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

void Renderer::drawUI(const UIObject* rootObject)
{
    SDL_Rect screenBounds{ .x = 0, .y = 0, .w = screenWidth, .h = screenHeight };
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
        if (!object.text.empty()) {
            drawUIText(object, parentBoundsAbs);
        }
        
        SDL_Rect dest = parentBoundsAbs;
        if (!object.textureFilepath.empty()) {
            dest = getUIDrawDest(object.anchor, object.bounds, parentBoundsAbs);
            SDL_RenderCopyEx(
                renderer,
                texture(object.textureFilepath).texture,
                nullptr,
                &dest,
                object.rotation,
                nullptr,
                SDL_FLIP_NONE);
        }
        
        for (const auto& subobject : object.subobjects) {
            drawUI(subobject, dest);
        }
    }
}

void Renderer::drawUIText(const struct UIObject& object, const SDL_Rect& parentBoundsAbs)
{
    auto* textSurface = TTF_RenderText_Blended(font, object.text.c_str(), { 255, 255, 255, 255 });
    SDL_Rect textBounds{
        object.bounds.x,
        object.bounds.y,
        textSurface->w,
        textSurface->h
    };
    SDL_Rect dest = getUIDrawDest(object.anchor, textBounds, parentBoundsAbs);
    
    auto* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopyEx(
        renderer,
        texture,
        nullptr,
        &dest,
        object.rotation,
        nullptr,
        SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(textSurface);
}

SDL_Rect Renderer::getUIDrawDest(UIAnchor anchor, const struct SDL_Rect& objectBounds, const SDL_Rect& parentBoundsAbs) const
{
    SDL_Rect dest = objectBounds;
    dest.x *= hidpiMult;
    dest.y *= hidpiMult;
    // UI assets are 2x size for HiDPI, scale down for non-HiDPI screens
    dest.w /= 2 / hidpiMult;
    dest.h /= 2 / hidpiMult;
    
    // x
    switch(anchor) {
        case UIAnchor::TopLeft:
        case UIAnchor::Left:
        case UIAnchor::BottomLeft:
            dest.x += parentBoundsAbs.x;
            break;
        case UIAnchor::Top:
        case UIAnchor::Center:
        case UIAnchor::Bottom:
            dest.x += parentBoundsAbs.x + parentBoundsAbs.w / 2 - dest.w / 2;
            break;
        case UIAnchor::TopRight:
        case UIAnchor::Right:
        case UIAnchor::BottomRight:
            dest.x += parentBoundsAbs.x + parentBoundsAbs.w - dest.w;
            break;
        case UIAnchor::World:
            break;
    }
    
    // y
    switch(anchor) {
        case UIAnchor::TopLeft:
        case UIAnchor::Top:
        case UIAnchor::TopRight:
            dest.y += parentBoundsAbs.y;
            break;
        case UIAnchor::Left:
        case UIAnchor::Center:
        case UIAnchor::Right:
            dest.y += parentBoundsAbs.y + parentBoundsAbs.h / 2 - dest.h / 2;
            break;
        case UIAnchor::BottomLeft:
        case UIAnchor::Bottom:
        case UIAnchor::BottomRight:
            dest.y += parentBoundsAbs.y + parentBoundsAbs.h - dest.h;
            break;
        case UIAnchor::World:
            break;
    }
    
    return dest;
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

const UIObject* Renderer::uiObjectAt(const UIObject* rootObject, const SDL_Point& screenCoords) const
{
    SDL_Rect screenBounds{ .x = 0, .y = 0, .w = screenWidth, .h = screenHeight };
    SDL_Point coords{ (int)(screenCoords.x * hidpiMult), (int)(screenCoords.y * hidpiMult) };
    for (auto it = rootObject->subobjects.rbegin(); it != rootObject->subobjects.rend(); it++) {
        if (auto* p = uiObjectAtRecursive(*it, screenBounds, coords)) return p;
    }
    return nullptr;
}

const UIObject* Renderer::uiObjectAtRecursive(const UIObject& object, const SDL_Rect& parentBoundsAbs, const SDL_Point& screenCoords) const
{
    SDL_Rect dest = parentBoundsAbs;
    if (!object.textureFilepath.empty()) {
        dest = getUIDrawDest(object.anchor, object.bounds, parentBoundsAbs);
    }
    
    for (auto it = object.subobjects.rbegin(); it != object.subobjects.rend(); it++) {
        if (auto* p = uiObjectAtRecursive(*it, dest, screenCoords)) return p;
    }
    
    if (object.bAcceptsInput && SDL_PointInRect(&screenCoords, &dest)) {
        return &object;
    }
    else {
        return nullptr;
    }
}

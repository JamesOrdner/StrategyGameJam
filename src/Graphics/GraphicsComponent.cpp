#include "GraphicsComponent.hpp"
#include "Sprite.hpp"
#include "Renderer.hpp"
#include "../Engine/GameObject.hpp"

GraphicsComponent::GraphicsComponent(class GameObject* owner) :
    GameObjectComponent(owner),
    renderDepth(RenderDepth::Terrain),
    oldRenderDepth(RenderDepth::Terrain)
{
}

GraphicsComponent::~GraphicsComponent()
{
}

void GraphicsComponent::setSprite(int width, int height, const SDL_Color& color)
{
    auto* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    Uint32 mappedColor = SDL_MapRGBA(pixelFormat, color.r, color.g, color.b, color.a);
    SDL_FreeFormat(pixelFormat);
    sprite = std::make_unique<Sprite>(renderer->sdlRenderer(), SDL_Rect{ 0, 0, .w = width, .h = height }, mappedColor);
}

SDL_Point GraphicsComponent::setSprite(const std::string& filepath)
{
    sprite = std::make_unique<Sprite>(filepath);
    return { sprite->bounds.w, sprite->bounds.h };
}

void GraphicsComponent::draw()
{
    if (!sprite) return;
    
    if (sprite->texture) {
        SDL_Rect dest = sprite->bounds;
        dest.x += owner->position.x;
        dest.y -= owner->position.y;
        renderer->draw(sprite->texture, dest, owner->rotation);
    }
    else {
        SDL_Point position{
            static_cast<int>(owner->position.x),
            static_cast<int>(owner->position.y)
        };
        renderer->draw(sprite->filepath, position, owner->rotation);
    }
}

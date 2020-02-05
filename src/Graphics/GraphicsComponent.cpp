#include "GraphicsComponent.hpp"
#include "Sprite.hpp"
#include "Renderer.hpp"
#include "../Engine/GameObject.hpp"

GraphicsComponent::GraphicsComponent(class GameObject* owner) :
    GameObjectComponent(owner)
{
}

GraphicsComponent::~GraphicsComponent()
{
}

void GraphicsComponent::setRenderer(const Renderer* renderer)
{
    this->renderer = renderer;
}

void GraphicsComponent::setSprite(int width, int height, SDL_Color color)
{
    
    auto* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    Uint32 mappedColor = SDL_MapRGBA(pixelFormat, color.r, color.g, color.b, color.a);
    SDL_FreeFormat(pixelFormat);
    sprite = std::make_unique<Sprite>(renderer->sdlRenderer(), SDL_Rect{ 0, 0, .w = width, .h = height }, mappedColor);
}

void GraphicsComponent::draw()
{
    if (!sprite) return;
    renderer->draw(sprite->texture, sprite->bounds, owner->rotation);
}

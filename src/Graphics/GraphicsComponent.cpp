#include "GraphicsComponent.hpp"
#include "Sprite.hpp"
#include "Renderer.hpp"

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
    Uint32 white = 0xFFFFFFFF;
    sprite = std::make_unique<Sprite>(renderer->sdlRenderer(), SDL_Rect{ .w = width, .h = height }, white);
}

void GraphicsComponent::draw(const SDL_Point& cameraPosition)
{
    if (!sprite) return;
    SDL_Rect dest = sprite->bounds;
    dest.x -= cameraPosition.x;
    dest.y -= cameraPosition.y;
    renderer->draw(sprite->texture, dest, 0);
}

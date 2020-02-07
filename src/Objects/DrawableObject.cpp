#include "DrawableObject.hpp"
#include "../Graphics/GraphicsComponent.hpp"

DrawableObject::DrawableObject(World* world, const SDL_FPoint& position) :
    GameObject(world, position)
{
    graphicsComponent = createComponent<GraphicsComponent>();
}

void DrawableObject::setSprite(int width, int height, const struct SDL_Color& color)
{
    graphicsComponent->setSprite(width, height, color);
    bounds = { width, height };
}

void DrawableObject::setSprite(const std::string& filepath)
{
    bounds = graphicsComponent->setSprite(filepath);
}

void DrawableObject::setRenderDepth(RenderDepth depth)
{
    graphicsComponent->renderDepth = depth;
}

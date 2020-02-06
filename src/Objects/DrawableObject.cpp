#include "DrawableObject.hpp"
#include "../Graphics/GraphicsComponent.hpp"

DrawableObject::DrawableObject(World* world) :
    GameObject(world)
{
    graphicsComponent = createComponent<GraphicsComponent>();
}

void DrawableObject::setSprite(int width, int height, const struct SDL_Color& color)
{
    graphicsComponent->setSprite(width, height, color);
}

void DrawableObject::setSprite(const std::string& filepath)
{
    graphicsComponent->setSprite(filepath);
}

void DrawableObject::setRenderDepth(RenderDepth depth)
{
    graphicsComponent->renderDepth = depth;
}

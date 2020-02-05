#include "DrawableObject.hpp"
#include "../Graphics/GraphicsComponent.hpp"

DrawableObject::DrawableObject(const class Engine* engine) :
    GameObject(engine)
{
    auto* graphicsComponent = createComponent<GraphicsComponent>();
    graphicsComponent->setSprite(100, 100, SDL_Color{});
}

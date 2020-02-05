#include "Graphics.hpp"
#include "GraphicsComponent.hpp"
#include "Renderer.hpp"
#include "../Objects/Camera.hpp"
#include <algorithm>

Graphics::Graphics() :
    camera(nullptr)
{
}

Graphics::~Graphics()
{
}

void Graphics::init()
{
    renderer = std::make_unique<Renderer>();
}

void Graphics::deinit()
{
    renderer.reset();
}

bool Graphics::execute(uint32_t deltaTime)
{
    renderer->clear();
    renderer->zoom = camera->zoomLevel();
    renderer->cameraOffset = {
        static_cast<int>(camera->position.x),
        static_cast<int>(camera->position.y)
    };
    
    for (auto& comp : graphicsComponents) comp->draw();
    
    renderer->present();
    return true;
}

void Graphics::registerComponent(GameObjectComponent* component)
{
    if (auto* graphicsComponent = dynamic_cast<GraphicsComponent*>(component)) {
        graphicsComponent->setRenderer(renderer.get());
        graphicsComponents.emplace_back(graphicsComponent);
    }
}

void Graphics::unregisterComponent(GameObjectComponent* component)
{
    auto* graphicsComponent = dynamic_cast<GraphicsComponent*>(component);
    auto it = std::remove(graphicsComponents.begin(), graphicsComponents.end(), graphicsComponent);
    if (it != graphicsComponents.end()) graphicsComponents.erase(it);
}

void Graphics::setCamera(const Camera* cameraObject)
{
    camera = cameraObject;
}

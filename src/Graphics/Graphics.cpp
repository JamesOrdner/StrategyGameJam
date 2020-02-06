#include "Graphics.hpp"
#include "GraphicsComponent.hpp"
#include "Renderer.hpp"
#include "../Objects/Camera.hpp"
#include <algorithm>

Graphics::Graphics(const Engine* engine) :
    GameSystem(engine),
    camera(nullptr),
    rootUIObject(nullptr)
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
    renderMap.clear();
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
    
    // draw world
    for (auto& layer : renderMap) {
        size_t i = 0;
        size_t removedComponents = 0;
        while (i < layer.second.size()) {
            GraphicsComponent* comp = layer.second[i];
            if (comp->renderDepth <= comp->oldRenderDepth) comp->draw();
            if (comp->renderDepth == comp->oldRenderDepth) {
                i++;
                continue;
            }
            
            layer.second.erase(layer.second.begin() + i);
            renderMap[comp->renderDepth].push_back(comp);
            comp->oldRenderDepth = comp->renderDepth;
            removedComponents++;
        }
    }
    
    // draw UI
    renderer->drawUI(rootUIObject);
    
    renderer->present();
    return true;
}

void Graphics::registerComponent(GameObjectComponent* component)
{
    if (auto* graphicsComponent = dynamic_cast<GraphicsComponent*>(component)) {
        graphicsComponent->renderer = renderer.get();
        graphicsComponents.push_back(graphicsComponent);
        renderMap[graphicsComponent->renderDepth].push_back(graphicsComponent);
    }
}

void Graphics::unregisterComponent(GameObjectComponent* component)
{
    auto* graphicsComponent = dynamic_cast<GraphicsComponent*>(component);
    if (!graphicsComponent) return;
    
    // remove from component list
    auto it = std::remove(graphicsComponents.begin(), graphicsComponents.end(), graphicsComponent);
    if (it != graphicsComponents.end()) graphicsComponents.erase(it);
    
    // remove from renderMap
    auto& layer = renderMap[graphicsComponent->oldRenderDepth];
    layer.erase(std::remove(layer.begin(), layer.end(), graphicsComponent));
}

void Graphics::setCamera(const Camera* cameraObject)
{
    camera = cameraObject;
}

void Graphics::setRootUIObject(const struct UIObject* object)
{
    rootUIObject = object;
}

SDL_Point Graphics::screenToWorldCoords(const SDL_Point& point) const
{
    return renderer->screenToWorldCoords(point);
}

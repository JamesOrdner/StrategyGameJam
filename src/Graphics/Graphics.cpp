#include "Graphics.hpp"
#include "Renderer.hpp"

Graphics::Graphics()
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
    renderer->draw();
    return true;
}

void Graphics::registerComponent(GameObjectComponent* component)
{
    
}

void Graphics::unregisterComponent(GameObjectComponent* component)
{
    
}

#include "Engine.hpp"
#include "World.hpp"
#include "../Graphics/Graphics.hpp"
#include "../Input/Input.hpp"
#include <SDL.h>
#include <iostream>

// TEMP
#include "../Objects/Camera.hpp"
#include "../Objects/DrawableObject.hpp"

Engine::Engine()
{
    graphics = std::make_unique<Graphics>();
    input = std::make_unique<Input>();
}

Engine::~Engine()
{
    
}

void Engine::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL failed to initialize!");
    };
    
    graphics->init();
    input->init();
    
    // TEMPORARY set up initial world
    auto& world = worlds.emplace_back(std::make_unique<World>(this));
    auto* camera = world->spawnObject<Camera>();
    world->spawnObject<DrawableObject>();
    graphics->setCamera(camera);
}

void Engine::deinit()
{
    worlds.clear();
    input->deinit();
    graphics->deinit();
    SDL_Quit();
}

void Engine::run()
{
    uint32_t time = SDL_GetTicks();
    while (true) {
        uint32_t deltaTime = SDL_GetTicks() - time;
        time += deltaTime;
        
        // process input and check for exit request
        if (!input->execute(deltaTime)) break;
        
        // tick all worlds/objects
        for (auto& world : worlds) world->tick(deltaTime);
        
        // execute all other systems
        graphics->execute(deltaTime);
    }
}

void Engine::registerComponent(GameObjectComponent* component) const
{
    // forward to all components, let them deal with dynamic casting
    graphics->registerComponent(component);
    input->registerComponent(component);
}

void Engine::unregisterComponent(GameObjectComponent* component) const
{
    graphics->unregisterComponent(component);
    input->unregisterComponent(component);
}

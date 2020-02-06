#include "Engine.hpp"
#include "World.hpp"
#include "GameState.hpp"
#include "../Graphics/Graphics.hpp"
#include "../Input/Input.hpp"
#include "../AI/AI.hpp"
#include "../Physics/Physics.hpp"
#include "../UI/UI.hpp"
#include <SDL.h>
#include <iostream>

// TEMP
#include "../Objects/Camera.hpp"
#include "../Objects/Actor.hpp"

Engine::Engine()
{
    graphics = std::make_unique<Graphics>(this);
    input = std::make_unique<Input>(this);
    ai = std::make_unique<AI>(this);
    physics = std::make_unique<Physics>(this);
    ui = std::make_unique<UI>(this);
    
    gameState = std::make_unique<GameState>(this);
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
    ai->init();
    physics->init();
    ui->init();
    
    graphics->setRootUIObject(ui->rootUIObjectPtr());
    
    auto& world = worlds.emplace_back(std::make_unique<World>(this));
    auto* camera = world->spawnObject<Camera>();
    graphics->setCamera(camera);
    
    gameState->startGame();

}

void Engine::deinit()
{
    worlds.clear();
    physics->deinit();
    ui->deinit();
    ai->deinit();
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
        ai->execute(deltaTime);
        physics->execute(deltaTime);
        ui->execute(deltaTime);
        graphics->execute(deltaTime);
    }
}

void Engine::registerComponent(GameObjectComponent* component) const
{
    // forward to all components, let them deal with dynamic casting
    graphics->registerComponent(component);
    input->registerComponent(component);
    ai->registerComponent(component);
    physics->registerComponent(component);
    ui->registerComponent(component);
}

void Engine::unregisterComponent(GameObjectComponent* component) const
{
    graphics->unregisterComponent(component);
    input->unregisterComponent(component);
    ai->unregisterComponent(component);
    physics->unregisterComponent(component);
    ui->registerComponent(component);
}

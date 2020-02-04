#include "Engine.hpp"
#include "GWorld.hpp"
#include "../Graphics/Renderer.hpp"
#include "../Input/Input.hpp"
#include <SDL.h>
#include <iostream>

Engine::Engine()
{
    renderer = std::make_unique<Renderer>();
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
    
    renderer->init();
    input->init();
}

void Engine::deinit()
{
    input->deinit();
    renderer->deinit();
    SDL_Quit();
}

void Engine::run()
{
    uint32_t time = SDL_GetTicks();
    while (true) {
        uint32_t deltaTime = SDL_GetTicks() - time;
        time += deltaTime;
        
        if (!input->execute(deltaTime)) break;
        renderer->execute(deltaTime);
    }
}

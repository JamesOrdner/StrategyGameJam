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
}

void Engine::deinit()
{
    renderer->deinit();
    SDL_Quit();
}

void Engine::run()
{
    while (input->processInput()) {
        
    }
}

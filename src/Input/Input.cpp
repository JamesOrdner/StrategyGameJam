#include "Input.hpp"
#include <SDL_events.h>

Input::Input()
{
    
}

Input::~Input()
{
    
}

bool Input::execute(uint32_t deltaTime)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
    }
    
    return true;
}

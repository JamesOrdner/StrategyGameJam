#include "Input.hpp"
#include "InputComponent.hpp"
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
        else if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN) {
            processKeyEvent(event);
        }
        else if(event.type == SDL_MOUSEWHEEL) {
            execCallback(InputEvent::CameraZoom, static_cast<float>(event.wheel.y));
        }
    }
    
    return true;
}

void Input::registerComponent(GameObjectComponent* component)
{
    if (auto* inputComponent = dynamic_cast<InputComponent*>(component)) {
        inputComponents.emplace(inputComponent);
    }
}

void Input::unregisterComponent(GameObjectComponent* component)
{
    auto* inputComponent = dynamic_cast<InputComponent*>(component);
    inputComponents.erase(inputComponent);
}

void Input::execCallback(InputEvent event, float value)
{
    for (auto& comp : inputComponents) comp->executeEvent(event, value);
}

void Input::processKeyEvent(const SDL_Event& event)
{
    auto key = event.key.keysym.scancode;
    if (key == SDL_SCANCODE_A || key == SDL_SCANCODE_D) {
        auto* kbstate = SDL_GetKeyboardState(nullptr);
        if (kbstate[SDL_SCANCODE_A] && !kbstate[SDL_SCANCODE_D]) {
            execCallback(InputEvent::Camera_X, -1.f);
        }
        else if (!kbstate[SDL_SCANCODE_A] && kbstate[SDL_SCANCODE_D]) {
            execCallback(InputEvent::Camera_X, 1.f);
        }
        else {
            execCallback(InputEvent::Camera_X, 0.f);
        }
    }
    else if (key == SDL_SCANCODE_W || key == SDL_SCANCODE_S) {
        auto* kbstate = SDL_GetKeyboardState(nullptr);
        if (kbstate[SDL_SCANCODE_W] && !kbstate[SDL_SCANCODE_S]) {
            execCallback(InputEvent::Camera_Y, 1.f);
        }
        else if (!kbstate[SDL_SCANCODE_W] && kbstate[SDL_SCANCODE_S]) {
            execCallback(InputEvent::Camera_Y, -1.f);
        }
        else {
            execCallback(InputEvent::Camera_Y, 0.f);
        }
    }
}

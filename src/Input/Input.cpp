#include "Input.hpp"
#include "InputComponent.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/GameState.hpp"
#include "../Graphics/Graphics.hpp"
#include "../Physics/Physics.hpp"
#include "../Objects/Actor.hpp"
#include <SDL_events.h>

Input::Input(const Engine* engine) :
    GameSystem(engine)
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
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            SDL_Point screenCoords;
            SDL_GetMouseState(&screenCoords.x, &screenCoords.y);
            SDL_Point worldCoords = engine->graphicsSystem()->screenToWorldCoords(screenCoords);
            if (auto* selected = engine->physicsSystem()->objectAt(worldCoords)) {
                if (auto* actor = dynamic_cast<Actor*>(selected)) {
                    engine->gameStatePtr()->selectedActors.clear();
                    engine->gameStatePtr()->selectedActors.push_back(actor);
                }
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
            SDL_Point screenCoords;
            SDL_GetMouseState(&screenCoords.x, &screenCoords.y);
            SDL_Point worldCoords = engine->graphicsSystem()->screenToWorldCoords(screenCoords);
            for (auto& actor : engine->gameStatePtr()->selectedActors) {
                SDL_FPoint dest{ static_cast<float>(worldCoords.x), static_cast<float>(worldCoords.y) };
                actor->setDestination(dest);
            }
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

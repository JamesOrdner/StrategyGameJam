#include "Input.hpp"
#include "InputComponent.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/GameState.hpp"
#include "../Graphics/Graphics.hpp"
#include "../Physics/Physics.hpp"
#include "../UI/UI.hpp"
#include "../Objects/Actor.hpp"

Input::Input(const Engine* engine) :
    GameSystem(engine),
    ui(nullptr)
{
    
}

Input::~Input()
{
    
}

bool Input::execute(uint32_t deltaTime)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if ((event.type == SDL_QUIT) ||
            (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
            return false;
        }
        
        // UI input
        if (event.type == SDL_MOUSEBUTTONDOWN ||
            event.type == SDL_MOUSEMOTION) {
            const UIObject* uiObject = engine->graphicsSystem()->uiObjectAt({ event.motion.x, event.motion.y });
            if (ui->processInput(event, uiObject)) continue;
        }
        
        if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN) {
            processKeyEvent(event);
        }
        else if(event.type == SDL_MOUSEWHEEL) {
            execCallback(InputEvent::CameraZoom, static_cast<float>(event.wheel.y));
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            processPrimaryClick(event);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
            processSecondaryClick(event);
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

void Input::processPrimaryClick(const union SDL_Event& event)
{
    SDL_Point screenCoords;
    SDL_GetMouseState(&screenCoords.x, &screenCoords.y);
    SDL_Point worldCoords = engine->graphicsSystem()->screenToWorldCoords(screenCoords);
    if (auto* selected = engine->physicsSystem()->objectAt(worldCoords)) {
        if (auto* actor = dynamic_cast<Actor*>(selected)) {
            bool bMultiSelect = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LSHIFT];
            engine->gameStatePtr()->actorSelected(actor, bMultiSelect, false);
        }
    }
    else {
        engine->gameStatePtr()->terrainSelected(worldCoords, false);
    }
}

void Input::processSecondaryClick(const union SDL_Event& event)
{
    SDL_Point screenCoords;
    SDL_GetMouseState(&screenCoords.x, &screenCoords.y);
    SDL_Point worldCoords = engine->graphicsSystem()->screenToWorldCoords(screenCoords);
    if (auto* selected = engine->physicsSystem()->objectAt(worldCoords)) {
        if (auto* actor = dynamic_cast<Actor*>(selected)) {
            bool bMultiSelect = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LSHIFT];
            engine->gameStatePtr()->actorSelected(actor, bMultiSelect, true);
        }
    }
    else {
        engine->gameStatePtr()->terrainSelected(worldCoords, true);
    }
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

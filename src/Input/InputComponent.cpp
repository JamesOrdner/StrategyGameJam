#include "InputComponent.hpp"

InputComponent::InputComponent(class GameObject* owner) :
    GameObjectComponent(owner)
{
}

void InputComponent::executeEvent(InputEvent event, float value)
{
    auto it = callbacks.find(event);
    if (it != callbacks.end()) it->second(value);
}

void InputComponent::registerEvent(InputEvent event, InputCallback callback)
{
    callbacks[event] = callback;
}

void InputComponent::unregisterEvent(InputEvent event)
{
    callbacks.erase(event);
}

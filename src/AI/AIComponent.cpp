#include "AIComponent.hpp"

AIComponent::AIComponent(class GameObject* owner) :
    GameObjectComponent(owner),
    movementSpeed(0.1f)
{
}

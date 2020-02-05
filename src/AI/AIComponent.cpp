#include "AIComponent.hpp"
#include <climits> // TEMP

AIComponent::AIComponent(class GameObject* owner) :
    GameObjectComponent(owner),
    movementSpeed(0.1f)
{
    // TEMP
    target = {
        static_cast<float>(rand()) / INT_MAX * 1500 - 750,
        static_cast<float>(rand()) / INT_MAX * 1500 - 750
    };
}

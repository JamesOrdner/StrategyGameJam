#include "AIComponent.hpp"
#include "../Objects/Actor.hpp"

AIComponent::AIComponent(class GameObject* owner) :
    GameObjectComponent(owner),
    team(Team::Player),
    activity(AIActivity::Idle),
    attackRadius(500.f),
    attackRate(500),
    movementState(AIMovementState::Idle),
    bMobile(true),
    movementSpeed(0.1f),
    attackTimer(0)
{
    actor = dynamic_cast<Actor*>(owner);
    if (!actor) throw std::runtime_error("AIComponent may only be added to Actor objects!");
}

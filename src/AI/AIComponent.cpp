#include "AIComponent.hpp"
#include "../Objects/Actor.hpp"

AIComponent::AIComponent(class GameObject* owner) :
    GameObjectComponent(owner),
    team(Team::Player),
    attackRadius(500.f),
    attackRate(500),
    bMobile(false),
    movementSpeed(0.3f),
    bAttacksRanged(false),
    activity(AIActivity::Idle),
    movementState(AIMovementState::Idle),
    destination(owner->position),
    target(nullptr),
    attackTimer(0)
{
    actor = dynamic_cast<Actor*>(owner);
    if (!actor) throw std::runtime_error("AIComponent may only be added to Actor objects!");
}

void AIComponent::setDestination(const SDL_FPoint& dest)
{
    movementState = AIMovementState::MovingToLocation;
    activity = AIActivity::Idle;
    destination = dest;
    target = nullptr;
}

void AIComponent::setTarget(Actor* target)
{
    if (target->aiComponent->team != team) {
        movementState = AIMovementState::MovingToEnemy;
        activity = AIActivity::Attacking;
        this->target = target;
    }
}

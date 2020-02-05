#include "Actor.hpp"
#include "../AI/AIComponent.hpp"
#include "../Physics/PhysicsComponent.hpp"

Actor::Actor(const Engine* engine) :
    DrawableObject(engine)
{
    createComponent<AIComponent>();
    auto* physics = createComponent<PhysicsComponent>();
    physics->bounds = { .x = -50, .y = -50, .w = 100, .h = 100 };
}

void Actor::reduceHealth(int healthDeducted) 
{
    health -= healthDeducted;
}

int Actor::getHealth()
{
    return health;
}

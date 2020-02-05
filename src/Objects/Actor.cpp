#include "Actor.hpp"
#include "../AI/AIComponent.hpp"

Actor::Actor(const Engine* engine) :
    DrawableObject(engine)
{
    createComponent<AIComponent>();
}

void Actor::reduceHealth(int healthDeducted) 
{
    health -= healthDeducted;
}

int Actor::getHealth()
{
    return health;
}

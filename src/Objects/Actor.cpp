#include "Actor.hpp"

Actor::Actor(const class Engine* engine) :
    DrawableObject(engine)
{

}

void Actor::reduceHealth(int healthDeducted) 
{
    health -= healthDeducted;
}

int Actor::getHealth()
{
    return health;
}

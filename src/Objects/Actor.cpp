#include "Actor.hpp"
#include "../AI/AIComponent.hpp"
#include "../UI/UIComponent.hpp"
#include "../Physics/PhysicsComponent.hpp"

Actor::Actor(World* world, const SDL_FPoint& position) :
    DrawableObject(world, position),
    health(100)
{
    aiComponent = createComponent<AIComponent>();
    aiComponent->bMobile = true;
    aiComponent->setDestination(position);
    
    uiComponent = createComponent<UIComponent>();
    uiComponent->outlineBounds = { .x = -50, .y = -50, .w = 100, .h = 100 };
    
    auto* physics = createComponent<PhysicsComponent>();
    physics->bounds = { .x = -50, .y = -50, .w = 100, .h = 100 };
}

void Actor::attack(Actor* other)
{
    // simple placeholder insta-damage
    if (other->reduceHealth(10)) {
        world->destroyObject(other);
    }
}

bool Actor::reduceHealth(int healthDeducted)
{
    health -= healthDeducted;
    return health <= 0;
}

int Actor::getHealth()
{
    return health;
}

void Actor::setTeam(Team team)
{
    aiComponent->team = team;
}

void Actor::setSelected(bool selected)
{
    uiComponent->bSelected = selected;
}

void Actor::setDestination(const SDL_FPoint& dest)
{
    aiComponent->setDestination(dest);
}

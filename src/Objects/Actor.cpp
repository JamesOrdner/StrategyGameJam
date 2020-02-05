#include "Actor.hpp"
#include "../AI/AIComponent.hpp"
#include "../UI/UIComponent.hpp"
#include "../Physics/PhysicsComponent.hpp"

Actor::Actor(const Engine* engine) :
    DrawableObject(engine)
{
    aiComponent = createComponent<AIComponent>();
    
    uiComponent = createComponent<UIComponent>();
    uiComponent->outlineBounds = { .x = -50, .y = -50, .w = 100, .h = 100 };
    
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

void Actor::setSelected(bool selected)
{
    uiComponent->bSelected = selected;
}

void Actor::setDestination(const SDL_FPoint& dest)
{
    aiComponent->target = dest;
}


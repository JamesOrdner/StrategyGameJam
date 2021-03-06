#include "Actor.hpp"
#include "../AI/AIComponent.hpp"
#include "../UI/UIComponent.hpp"
#include "../Physics/Physics.hpp"

Actor::Actor(World* world, const SDL_FPoint& position) :
    DrawableObject(world, position),
    attackDamage(10),
    aiComponent(createComponent<AIComponent>()),
    health(100),
    killValue(1)
{
    uiComponent = createComponent<UIComponent>();
    
    aiComponent->bMobile = true;
    aiComponent->setDestination(position);
    
    setPhysics(PhysicsType::Actor);
}

bool Actor::attack(Actor* other)
{
    if (aiComponent->bAttacksRanged) {
        
        return true;
    }
    else {
        if (world->engine->physicsSystem()->colliding(this, other)) {
            if (other->reduceHealth(attackDamage)) {
                world->destroyObject(other);
            }
            return true;
        }
    }
    
    return false;
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

void Actor::setSelected(bool selected)
{
    uiComponent->bSelected = selected;
}

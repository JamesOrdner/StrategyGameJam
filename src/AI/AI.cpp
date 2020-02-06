#include "AI.hpp"
#include "AIComponent.hpp"
#include "../Engine/GameObject.hpp"
#include "../Objects/Actor.hpp"
#include "../Util/SDLMath.hpp"
#include <algorithm>

AI::AI(const Engine* engine) :
    GameSystem(engine)
{
}

bool AI::execute(uint32_t deltaTime)
{
    for (auto* comp : aiComponents) {
        if (comp->activity == AIActivity::Idle) {
            decideActivity(comp);
        }
        if (comp->bMobile && comp->movementState != AIMovementState::Idle) {
            doMovement(comp, deltaTime);
        }
        if (comp->activity == AIActivity::Attacking) {
            comp->attackTimer += deltaTime;
            if (comp->attackTimer >= comp->attackRate) {
                comp->actor->attack(comp->target);
                comp->attackTimer = 0;
            }
        }
    }
    return true;
}

void AI::registerComponent(class GameObjectComponent* component)
{
    if (auto* aiComponent = dynamic_cast<AIComponent*>(component)) {
        aiComponents.emplace_back(aiComponent);
    }
}

void AI::unregisterComponent(class GameObjectComponent* component)
{
    auto* aiComponent = dynamic_cast<AIComponent*>(component);
    if (!aiComponent) return;
    aiComponents.erase(std::remove(aiComponents.begin(), aiComponents.end(), aiComponent));
    
    // remove from any objects' targets
    for (auto* comp : aiComponents) {
        if (comp->target == aiComponent->actor) {
            comp->target = nullptr;
            comp->activity = AIActivity::Idle;
            if (comp->movementState == AIMovementState::MovingToObject) {
                comp->movementState = AIMovementState::Idle;
            }
        }
    }
}

void AI::decideActivity(class AIComponent* component)
{
    // check for enemies
    for (auto* compOther : aiComponents) {
        if (component->team == compOther->team) continue;
        if (dist(component->owner->position, compOther->owner->position) < component->attackRadius) {
            component->target = compOther->actor;
            component->activity = AIActivity::Attacking;
            component->movementState = AIMovementState::MovingToObject;
        }
    }
}

void AI::doMovement(class AIComponent* component, double deltaTime)
{
    SDL_FPoint dest;
    if (component->movementState == AIMovementState::MovingToLocation) {
        dest = component->destination;
    }
    else {
        dest = component->target->position;
    }
    
    SDL_FPoint dir = normalize(dest - component->owner->position);
    component->owner->position += dir * static_cast<float>(deltaTime) * component->movementSpeed;
    component->owner->rotation = atan2(dir.x, dir.y) * 180 / 3.14159265;
    
    if (dist(dest, component->owner->position) < component->movementSpeed * deltaTime) {
        component->movementState = AIMovementState::Idle;
    }
}

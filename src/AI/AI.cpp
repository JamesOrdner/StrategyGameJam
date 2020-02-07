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
        if (comp->team == Team::Player) {
            processFriendlyActor(comp, deltaTime);
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
            if (comp->movementState == AIMovementState::MovingToEnemy) {
                comp->movementState = AIMovementState::Idle;
            }
        }
    }
}

void AI::processFriendlyActor(class AIComponent* component, uint32_t deltaTime)
{
    // 1) Think
    if (component->movementState == AIMovementState::Idle) {
        if (component->activity == AIActivity::Idle) {
            if (Actor* enemy = searchForEnemy(component, component->destination)) {
                component->activity = AIActivity::Attacking;
                component->target = enemy;
            }
        }
        else if (component->activity == AIActivity::Attacking) {
            // check enemy still in range
            if (dist(component->destination, component->target->position) > component->attackRadius) {
                component->activity = AIActivity::Idle;
                component->target = nullptr;
            }
        }
        else {
            // building
        }
    }
    else if (component->movementState == AIMovementState::MovingToLocation) {
        if (component->activity == AIActivity::Idle) {
            Actor* enemy = searchForEnemy(component);
            if (!component->bAttacksRanged) {
                // melee units may attack enemies within range of the destination
                if (enemy && dist(component->destination, enemy->position) < component->attackRadius) {
                    component->movementState = AIMovementState::Idle;
                    component->target = enemy;
                }
            }
            else if (enemy) {
                // ranged units can attack enemies without breaking course
                component->activity = AIActivity::Attacking;
                component->target = enemy;
            }
        }
        else if (component->activity == AIActivity::Attacking) {
            // check enemy still in range
            if (dist(component->actor->position, component->target->position) > component->attackRadius) {
                component->activity = AIActivity::Idle;
                component->target = nullptr;
            }
        }
    }
    
    // 2) Do
    if (component->bMobile) {
        doMovement(component, deltaTime);
    }
    
    if (component->target) {
        component->attackTimer += deltaTime;
        if (component->attackTimer >= component->attackRate) {
            component->actor->attack(component->target);
            component->attackTimer = 0;
        }
    }
}

Actor* AI::searchForEnemy(AIComponent* component)
{
    for (auto* compOther : aiComponents) {
        if (component->team != compOther->team) {
            if (dist(component->owner->position, compOther->owner->position) < component->attackRadius) {
                return compOther->actor;
            }
        }
    }
    
    return nullptr;
}

Actor* AI::searchForEnemy(AIComponent* component, const SDL_FPoint& searchOrigin)
{
    for (auto* compOther : aiComponents) {
        if (component->team != compOther->team) {
            if (dist(searchOrigin, compOther->owner->position) < component->attackRadius) {
                return compOther->actor;
            }
        }
    }
    
    return nullptr;
}

void AI::doMovement(class AIComponent* component, double deltaTime)
{
    SDL_FPoint dest;
    if (component->target && (!component->bAttacksRanged || component->movementState == AIMovementState::MovingToEnemy)) {
        dest = component->target->position;
    }
    else {
        dest = component->destination;
    }
    float moveDist = static_cast<float>(deltaTime) * component->movementSpeed;
    
    if (dist(component->owner->position, dest) >= moveDist) {
        SDL_FPoint dir = normalize(dest - component->owner->position);
        component->owner->position += dir * moveDist;
        component->owner->rotation = atan2(dir.x, dir.y) * 180 / 3.14159265;
    }
    else {
        component->movementState = AIMovementState::Idle;
    }
}

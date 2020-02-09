#include "AI.hpp"
#include "AIComponent.hpp"
#include "../Engine/GameObject.hpp"
#include "../Objects/Actor.hpp"
#include "../Objects/Structure.hpp"
#include "../Util/SDLMath.hpp"
#include <algorithm>
#include <cfloat>
#include <random>

AI::AI(const Engine* engine) :
    GameSystem(engine)
{
}

bool AI::execute(uint32_t deltaTime)
{
    for (auto* component : aiComponents) {
        if (component->team == Team::Player) {
            processFriendlyActor(component, deltaTime);
        }
        else if (component->team == Team::Enemy){
            processEnemyActor(component, deltaTime);
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
    
    if (component->target && targetInRange(component)) {
        component->attackTimer += deltaTime;
        if (component->attackTimer >= component->attackRate) {
            if (component->actor->attack(component->target)) {
                // only reset if Actor able to attack
                component->attackTimer = 0;
            }
        }
    }
}

void AI::processEnemyActor(AIComponent* component, uint32_t deltaTime)
{
    // 1) Think
    if (!component->target) {
        // we should always have a target, find a structure to attack
        if (Actor* structure = searchForEnemyStructure(component)) {
            component->target = structure;
            component->destination = structure->position;
            component->movementState = AIMovementState::MovingToLocation;
        }
    }
    
    if (component->movementState == AIMovementState::MovingToLocation) {
        if (Actor* enemy = searchForEnemy(component)) {
            // prioritize attacking units over structures
            component->target = enemy;
            component->movementState = AIMovementState::MovingToEnemy;
        }
    }
    else if (component->movementState == AIMovementState::MovingToEnemy) {
        // check enemy still in range
        if (dist(component->actor->position, component->target->position) > component->attackRadius) {
            component->target = searchForEnemyStructure(component);
            component->movementState = AIMovementState::MovingToLocation;
        }
    }
    
    // 2) Do
    if (component->bMobile) {
        doMovement(component, deltaTime);
    }
    
    if (component->target && targetInRange(component)) {
        component->attackTimer += deltaTime;
        if (component->attackTimer >= component->attackRate) {
            if (component->actor->attack(component->target)) {
                // only reset if Actor able to attack
                component->attackTimer = 0;
            }
        }
    }
}

Actor* AI::searchForEnemy(AIComponent* component)
{
    return searchForEnemy(component, component->owner->position);
}

Actor* AI::searchForEnemy(AIComponent* component, const SDL_FPoint& searchOrigin)
{
    Actor* enemy = nullptr;
    float nearest = FLT_MAX;
    for (auto* compOther : aiComponents) {
        if (component->team != compOther->team && compOther->team != Team::None) {
            float d = dist(searchOrigin, compOther->owner->position);
            if (d < component->attackRadius && d < nearest) {
                enemy = compOther->actor;
                nearest = d;
            }
        }
    }
    return enemy;
}

Actor* AI::searchForEnemyStructure(AIComponent* component)
{
    std::vector<Structure*> structures;
    for (auto* compOther : aiComponents) {
        if (component->team == compOther->team || compOther->team == Team::None) continue;
        if (auto* s = dynamic_cast<Structure*>(compOther->actor)) {
            structures.push_back(s);
        }
    }
    if (structures.empty()) return nullptr;
    
    // sort by distance
    std::sort(
        structures.begin(),
        structures.end(),
        [p = component->owner->position](Structure* a, Structure* b) {
            return dist(p, a->position) < dist(p, b->position);
        }
    );
    
    // select target, preferring closer targets
    static std::random_device r;
    static std::default_random_engine randomEngine(r());
    static std::geometric_distribution<size_t> distribution(0.5); // distance preference
    return structures[distribution(randomEngine) % structures.size()];
}

bool AI::targetInRange(AIComponent* attacker, Actor* target)
{
    if (!target) target = attacker->target;
    if (!target) return false;
    return dist(attacker->actor->position, target->position) <= attacker->attackRadius;
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

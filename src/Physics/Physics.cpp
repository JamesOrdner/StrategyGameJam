#include "Physics.hpp"
#include "PhysicsComponent.hpp"
#include "../Engine/GameObject.hpp"
#include "../Util/SDLMath.hpp"
#include <algorithm>

Physics::Physics(const Engine* engine) :
    GameSystem(engine)
{
}

bool Physics::execute(uint32_t deltaTime)
{
    // simple collision repulsion "algorithm"
    float moveDist = static_cast<float>(deltaTime) * 0.1f;
    for (auto* component : physicsComponents) {
        switch (component->physicsType) {
            case PhysicsType::Actor:
                component->owner->position += getForce(component) * moveDist;
            default:
                break;
        }
    }
    
    return true;
}

SDL_FPoint Physics::getForce(const PhysicsComponent* component) const
{
    SDL_FPoint force = {};
    for (auto* compOther : physicsComponents) {
        if (component == compOther) continue;
        if (compOther->physicsType != PhysicsType::None) {
            if (colliding(component->owner, compOther->owner)) {
                force += normalize(component->owner->position - compOther->owner->position);
            }
        }
    }
    return force;
}

SDL_Rect Physics::objectWorldBounds(const GameObject* object) const
{
    const SDL_FPoint& pos = object->position;
    const SDL_Point& bounds = object->bounds.value();
    return {
        static_cast<int>(pos.x) - bounds.x / 2,
        static_cast<int>(pos.y) - bounds.y / 2,
        bounds.x,
        bounds.y
    };
}

void Physics::registerComponent(class GameObjectComponent* component)
{
    if (auto* physicsComponent = dynamic_cast<PhysicsComponent*>(component)) {
        physicsComponents.emplace_back(physicsComponent);
    }
}

void Physics::unregisterComponent(class GameObjectComponent* component)
{
    auto* physicsComponent = dynamic_cast<PhysicsComponent*>(component);
    auto it = std::remove(physicsComponents.begin(), physicsComponents.end(), physicsComponent);
    if (it != physicsComponents.end()) physicsComponents.erase(it);
}

GameObject* Physics::objectAt(const SDL_Point& coords) const
{
    for (const auto& comp : physicsComponents) {
        if (comp->physicsType != PhysicsType::None && comp->owner->bounds.has_value()) {
            SDL_Rect bounds = objectWorldBounds(comp->owner);
            if (SDL_PointInRect(&coords, &bounds)) return comp->owner;
        }
    }
    return nullptr;
}

std::vector<GameObject*> Physics::objectsIn(const SDL_Rect& rect) const
{
    std::vector<GameObject*> objects;
    for (const auto& comp : physicsComponents) {
        if (comp->physicsType != PhysicsType::None && comp->owner->bounds.has_value()) {
            if (colliding(comp->owner, rect)) objects.push_back(comp->owner);
        }
    }
    return objects;
}

bool Physics::colliding(const GameObject* a, const GameObject* b) const
{
    if (!a->bounds.has_value() || !b->bounds.has_value()) return false;
    SDL_Rect aBounds = objectWorldBounds(a);
    SDL_Rect bBounds = objectWorldBounds(b);
    
    if (aBounds.x >= bBounds.x + bBounds.w) return false;
    if (bBounds.x >= aBounds.x + aBounds.w) return false;
    if (aBounds.y >= bBounds.y + bBounds.h) return false;
    if (bBounds.y >= aBounds.y + aBounds.h) return false;
    return true;
}

bool Physics::colliding(const GameObject* a, const SDL_Rect& rect) const
{
    if (!a->bounds.has_value()) return false;
    SDL_Rect aBounds = objectWorldBounds(a);
    
    if (aBounds.x >= rect.x + rect.w) return false;
    if (rect.x >= aBounds.x + aBounds.w) return false;
    if (aBounds.y >= rect.y + rect.h) return false;
    if (rect.y >= aBounds.y + aBounds.h) return false;
    return true;
}

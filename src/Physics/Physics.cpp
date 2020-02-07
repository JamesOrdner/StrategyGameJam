#include "Physics.hpp"
#include "PhysicsComponent.hpp"
#include "../Engine/GameObject.hpp"
#include <algorithm>

Physics::Physics(const Engine* engine) :
    GameSystem(engine)
{
}

bool Physics::execute(uint32_t deltaTime)
{
    return true;
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
        if (comp->owner->bounds.has_value()) {
            const SDL_FPoint& pos = comp->owner->position;
            const SDL_Point& bounds = comp->owner->bounds.value();
            SDL_Rect rect{
                static_cast<int>(pos.x) - bounds.x / 2,
                static_cast<int>(pos.y) - bounds.y / 2,
                bounds.x,
                bounds.y
            };
            if (SDL_PointInRect(&coords, &rect)) return comp->owner;
        }
    }
    return nullptr;
}

#include "Physics.hpp"
#include "PhysicsComponent.hpp"
#include "../Engine/GameObject.hpp"

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
        SDL_Rect absBounds = comp->bounds;
        absBounds.x += comp->owner->position.x;
        absBounds.y += comp->owner->position.y;
        if (SDL_PointInRect(&coords, &absBounds)) return comp->owner;
    }
    return nullptr;
}

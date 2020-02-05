#include "AI.hpp"
#include "AIComponent.hpp"
#include "../Engine/GameObject.hpp"
#include "../Util/SDLMath.hpp"
#include <algorithm>

AI::AI(const Engine* engine) :
    GameSystem(engine)
{
}

bool AI::execute(uint32_t deltaTime)
{
    for (auto& comp : aiComponents) {
        if (comp->target.has_value()) {
            // TEMP until we have real physics
            SDL_FPoint dir = normalize(comp->target.value() - comp->owner->position);
            comp->owner->position += dir * static_cast<float>(deltaTime) * comp->movementSpeed;
            comp->owner->rotation = atan2(dir.x, dir.y) * 180 / 3.14159265;
            
            if (dist(comp->target.value(), comp->owner->position) < 1.f) {
                comp->target.reset();
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
    auto it = std::remove(aiComponents.begin(), aiComponents.end(), aiComponent);
    if (it != aiComponents.end()) aiComponents.erase(it);
}

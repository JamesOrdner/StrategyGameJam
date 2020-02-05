#include "AI.hpp"
#include "AIComponent.hpp"
#include <algorithm>

AI::AI()
{
}

bool AI::execute(uint32_t deltaTime)
{
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

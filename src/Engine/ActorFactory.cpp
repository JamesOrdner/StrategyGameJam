#include "ActorFactory.hpp"
#include "World.hpp"
#include "../Objects/Actor.hpp"
#include <SDL_rect.h>

int ActorFactory::unitCost(PlayerUnit unit, ResourceType resouce)
{
    switch (unit) {
        case PlayerUnit::Clubman:
            switch (resouce) {
                case ResourceType::Wood:    return 1;
                case ResourceType::Iron:    return 0;
                case ResourceType::Crystal: return 0;
                case ResourceType::Wolf:    return 0;
            }
            break;
    }
    return -1;
}

ResourceType ActorFactory::unitSpawnLocation(PlayerUnit unit)
{
    switch (unit) {
        case PlayerUnit::Clubman: return ResourceType::Wood;
    }
}

void ActorFactory::spawnUnit(World* world, PlayerUnit unit, const SDL_FPoint& position)
{
    switch (unit) {
        case PlayerUnit::Clubman:
            auto* a = world->spawnObject<Actor>(position);
            a->setSprite(50, 35, { 200, 200, 150, 255 });
            break;
    }
}

#include "ActorFactory.hpp"
#include "World.hpp"
#include "../Objects/Actor.hpp"
#include <SDL_rect.h>

int ActorFactory::unitCost(PlayerUnit unit, ResourceType resouce)
{
    switch (unit) {
        case PlayerUnit::Swordsman:
            switch (resouce) {
                case ResourceType::Wood: return 0;
            }
            break;
    }
}

void ActorFactory::spawnUnit(World* world, PlayerUnit unit, const SDL_FPoint& position)
{
    switch (unit) {
        case PlayerUnit::Swordsman:
            auto* a = world->spawnObject<Actor>(position);
            a->setSprite(50, 35, { 200, 200, 150, 255 });
            break;
    }
}

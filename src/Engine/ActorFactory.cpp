#include "ActorFactory.hpp"
#include "World.hpp"
#include "../AI/AIComponent.hpp"
#include "../Objects/Actor.hpp"
#include "../Util/SDLMath.hpp"
#include <SDL_rect.h>
#include <random>

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
    Actor* a;
    switch (unit) {
        case PlayerUnit::Clubman:
            a = world->spawnObject<Actor>(position);
            a->setSprite(50, 35, { 200, 200, 150, 255 });
            break;
    }
    
    static std::random_device r;
    static std::default_random_engine rGen(r());
    static std::uniform_real_distribution<float> dir(-1, 1);
    static std::uniform_real_distribution<float> dist(400, 800);
    
    SDL_FPoint spawnDir = normalize({ dir(rGen), dir(rGen) });
    a->aiComponent->setDestination(a->position + spawnDir * dist(rGen));
}

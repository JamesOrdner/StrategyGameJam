#ifndef ActorFactory_hpp
#define ActorFactory_hpp

#include "Types.hpp"

struct ActorFactory
{
    static int unitCost(PlayerUnit unit, ResourceType resouce);
    
    static void spawnUnit(class World* world, PlayerUnit unit, const struct SDL_FPoint& position);
};

#endif /* ActorFactory_hpp */

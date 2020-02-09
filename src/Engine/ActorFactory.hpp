#ifndef ActorFactory_hpp
#define ActorFactory_hpp

#include "Types.hpp"

struct ActorFactory
{
    static int unitCost(PlayerUnit unit, ResourceType resouce);
    
    /// Returns the ResourcePoint to spawn the unit at
    static ResourceType unitSpawnLocation(PlayerUnit unit);
    
    static void spawnUnit(class World* world, PlayerUnit unit, const struct SDL_FPoint& position);
};

#endif /* ActorFactory_hpp */

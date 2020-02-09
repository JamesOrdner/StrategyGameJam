#ifndef GameState_hpp
#define GameState_hpp

#include "Types.hpp"
#include <SDL_rect.h>
#include <vector>

class GameState
{
public:
    
    GameState(const class Engine* engine);
    
    void startGame();
    
    void tick(uint32_t deltaTime);
    
    void setResourcePoint(class ResourcePoint* point, ResourceType type);
    
    /// bMultiSelect == true if modifier key like shift is held.
    /// bCommand == true when right click (command), false if left click (selection)
    void actorSelected(class Actor* actor, bool bMultiSelect, bool bCommand);
    
    /// bCommand == true when right click (command), false if left click (selection)
    void terrainSelected(const SDL_Point& position, bool bCommand);
    
    void actorKilled(class Actor* actor);
    
    inline unsigned int getMoney() const { return money; }
    
    int getResourceCount(ResourceType resouce) const;
    
    bool isUnitBuildable(PlayerUnit unit) const;
    
    bool buildUnit(PlayerUnit unit);
    
private:
    
    const class Engine* const engine;
    
    std::vector<class Actor*> selectedActors;
    
    unsigned int money;

    uint32_t spawnTime;

    /// Time since last money update
    uint32_t moneyTimer;
    
    /// Time since last enemy unit spawn
    uint32_t enemyTimer;

    /// Time since last resource update
    uint32_t resourceTimer;
    
    struct Resource {
        class ResourcePoint* resourcePoint;
        bool bOwned;
        int value;
    };
    
    struct Resources {
        Resource wood;
        Resource iron;
        Resource crystal;
        Resource wolf;
        
        void addResouces(int amount) {
            if (wood.bOwned)    wood.value    += amount;
            if (iron.bOwned)    iron.value    += amount;
            if (crystal.bOwned) crystal.value += amount;
            if (wolf.bOwned)    wolf.value    += amount;
        }
    } resources;
};

#endif /* GameState_hpp */

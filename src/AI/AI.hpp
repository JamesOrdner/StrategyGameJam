#ifndef AI_hpp
#define AI_hpp

#include "../Engine/GameSystem.hpp"
#include <SDL_rect.h>
#include <vector>

class AI : public GameSystem
{
public:
    
    AI(const class Engine* engine);
    
    bool execute(uint32_t deltaTime) override;
    void registerComponent(class GameObjectComponent* component) override;
    void unregisterComponent(class GameObjectComponent* component) override;
    
private:
    
    /// All registered AI components
    std::vector<class AIComponent*> aiComponents;
    
    void processFriendlyActor(class AIComponent* component, uint32_t deltaTime);
    
    void processEnemyActor(class AIComponent* component, uint32_t deltaTime);
    
    /// Return enemy for component in range of Actor, or nullptr if no enemies found
    class Actor* searchForEnemy(class AIComponent* component);
    
    /// Return enemy for component in range of searchOrigin, or nullptr if no enemies found
    class Actor* searchForEnemy(class AIComponent* component, const SDL_FPoint& searchOrigin);
    
    /// Return an enemy structure, or nullptr if no enemy structures found
    class Actor* searchForEnemyStructure(class AIComponent* component);
    
    /// If target is nullptr, attacker's current target is used
    bool targetInRange(class AIComponent* attacker, class Actor* target = nullptr);
    
    void doMovement(class AIComponent* component, double deltaTime);
};

#endif /* AI_hpp */

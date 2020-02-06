#ifndef AI_hpp
#define AI_hpp

#include "../Engine/GameSystem.hpp"
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
    
    void decideActivity(class AIComponent* component);
    
    void doMovement(class AIComponent* component, double deltaTime);
};

#endif /* AI_hpp */

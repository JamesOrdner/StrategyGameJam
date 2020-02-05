#ifndef AI_hpp
#define AI_hpp

#include "../Engine/GameSystem.hpp"
#include <vector>

class AI : public GameSystem
{
public:
    
    AI();
    
    bool execute(uint32_t deltaTime) override;
    void registerComponent(class GameObjectComponent* component) override;
    void unregisterComponent(class GameObjectComponent* component) override;
    
private:
    
    /// All registered AI components
    std::vector<class AIComponent*> aiComponents;
};

#endif /* AI_hpp */

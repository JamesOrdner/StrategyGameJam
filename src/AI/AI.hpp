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
    
    /// Return enemy for component in range of Actor, or nullptr if no enemies found
    class Actor* searchForEnemy(class AIComponent* component);
    
    /// Return enemy for component in range of searchOrigin, or nullptr if no enemies found
    class Actor* searchForEnemy(class AIComponent* component, const SDL_FPoint& searchOrigin);
    
    void doMovement(class AIComponent* component, double deltaTime);
};

#endif /* AI_hpp */

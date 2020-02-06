#ifndef AIComponent_hpp
#define AIComponent_hpp

#include "../Engine/GameObjectComponent.hpp"
#include "../Engine/Types.hpp"
#include <SDL_rect.h>

enum class AIMovementState
{
    Idle,
    MovingToLocation,
    MovingToObject
};

enum class AIActivity
{
    Idle,
    Attacking,
    Building
};

class AIComponent : public GameObjectComponent
{
public:
    
    AIComponent(class GameObject* owner);
    
    Team team;
    
    AIActivity activity;
    
    float attackRadius;
    
    /// The number of ms between each attack
    uint32_t attackRate;
    
    AIMovementState movementState;
    
    bool bMobile;
    
    float movementSpeed;
    
    /// The actor's movement target when movementState == MovingToLocation
    SDL_FPoint destination;
    
    /// The actor's movement target when movementState == MovingToObject
    class Actor* target;
    
private:
    
    friend class AI;
    
    /// Owning actor object
    class Actor* actor;
    
    /// Time since last attack
    uint32_t attackTimer;
};

#endif /* AIComponent_hpp */

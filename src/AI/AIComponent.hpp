#ifndef AIComponent_hpp
#define AIComponent_hpp

#include "../Engine/GameObjectComponent.hpp"
#include "../Engine/Types.hpp"
#include <SDL_rect.h>

enum class AIMovementState
{
    Idle,
    MovingToLocation,
    MovingToEnemy
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
    
    /// Engagement distance, for both ranged and melee units
    float attackRadius;
    
    /// The number of ms between each attack
    uint32_t attackRate;
    
    /// Can this Actor move?
    bool bMobile;
    
    /// True if the Actor has a ranged attack, false if it has a melee attack
    bool bAttacksRanged;
    
    float movementSpeed;
    
    void setDestination(const SDL_FPoint& dest);
    
    void setTarget(class Actor* target);
    
private:
    
    friend class AI;
    
    /// Owning actor object
    class Actor* actor;
    
    AIActivity activity;
    
    AIMovementState movementState;
    
    /// The actor's movement target when movementState == MovingToLocation
    SDL_FPoint destination;
    
    /// The actor's movement target when movementState == MovingToObject
    class Actor* target;
    
    /// Time since last attack
    uint32_t attackTimer;
};

#endif /* AIComponent_hpp */

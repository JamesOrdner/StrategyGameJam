#ifndef Actor_hpp
#define Actor_hpp

#include "DrawableObject.hpp"
#include "../Engine/Types.hpp"

class Actor : public DrawableObject
{
public:
    
    Actor(class World* world, const SDL_FPoint& position);
    
    virtual int buildCost(ResourceType resource) const { return 0; };
    
    virtual void attack(Actor* other);
    
    /// Reduce the actor's health by an amount, returning true if the actor is killed
    bool reduceHealth(int amount);
    
    int getHealth();
    
    inline int getKillValue() const { return killValue; }
    
    void setSelected(bool selected);
    
    int attackDamage;
    
    class AIComponent* const aiComponent;
    
protected:
    
    class UIComponent* uiComponent;
    
    int health;
    
    /// Money granted for killing this unit
    int killValue;
};

#endif /* Actor_hpp */

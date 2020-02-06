#ifndef Actor_hpp
#define Actor_hpp

#include "DrawableObject.hpp"
#include "../Engine/Types.hpp"

class Actor : public DrawableObject
{
public:
    
    Actor(class World* world);
    
    virtual int buildCost(ResourceType resource) const { return 0; };
    
    virtual void attack(Actor* other);
    
    /// Reduce the actor's health by an amount, returning true if the actor is killed
    bool reduceHealth(int amount);
    
    int getHealth();
    
    void setTeam(Team team);
    
    void setSelected(bool selected);
    
    void setDestination(const SDL_FPoint& dest);
    
private:
    
    class AIComponent* aiComponent;
    
    class UIComponent* uiComponent;
    
    int health;
};

#endif /* Actor_hpp */

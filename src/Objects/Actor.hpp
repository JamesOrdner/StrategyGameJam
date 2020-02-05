#ifndef Actor_hpp
#define Actor_hpp

#include "DrawableObject.hpp"

class Actor : public DrawableObject
{
public:
    
    Actor(const class Engine* engine);
    virtual int getRequiredResource(int resource) const { return 0; };
    void reduceHealth(int amount);
    int getHealth();
    
private:
    
    unsigned int health;
};

#endif /* Actor_hpp */

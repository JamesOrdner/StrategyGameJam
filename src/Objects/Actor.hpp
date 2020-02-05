#ifndef Actor_hpp
#define Actor_hpp

#include "DrawableObject.hpp"

class Actor : public DrawableObject
{
    public:
        Actor(const class Engine* engine);
        virtual int getRequiredResource(int resource) = 0;
        void reduceHealth(int amount);
        int getHealth();

    private:
        unsigned int health;
        float movementSpeed;
};

#endif /* Actor_hpp */

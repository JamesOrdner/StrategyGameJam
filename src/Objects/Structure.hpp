#ifndef Structure_hpp
#define Structure_hpp

#include "Actor.hpp"

class Structure : public Actor
{
public:
    
    Structure(class World* world, const SDL_FPoint& position);
    
};

#endif /* Structure_hpp */

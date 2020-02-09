#ifndef ResourcePoint_hpp
#define ResourcePoint_hpp

#include "Structure.hpp"

class ResourcePoint : public Structure
{
public:
    
    ResourcePoint(class World* world, const SDL_FPoint& position, ResourceType resource);
    
    const ResourceType resource;
};

#endif /* ResourcePoint_hpp */

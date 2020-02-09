#include "ResourcePoint.hpp"

ResourcePoint::ResourcePoint(class World* world, const SDL_FPoint& position, ResourceType resource) :
    Structure(world, position),
    resource(resource)
{
    
}

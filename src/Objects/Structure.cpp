#include "Structure.hpp"
#include "../AI/AIComponent.hpp"

Structure::Structure(World* world, const SDL_FPoint& position) :
    Actor(world, position)
{
    aiComponent->bMobile = false;
    setPhysics(PhysicsType::Static);
}

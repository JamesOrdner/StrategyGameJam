#include "GWorld.hpp"
#include "Engine.hpp"
#include "GObject.hpp"

GWorld::GWorld(const Engine* engine) :
    engine(engine)
{
    
}

GWorld::~GWorld()
{
    
}

void GWorld::tick(uint32_t deltaTime)
{
    for (auto& obj : objects) obj->tick(deltaTime);
}

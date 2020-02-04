#include "World.hpp"
#include "Engine.hpp"
#include "GameObject.hpp"

World::World(const Engine* engine) :
    engine(engine)
{
    
}

World::~World()
{
    
}

void World::tick(uint32_t deltaTime)
{
    for (auto& obj : objects) obj->tick(deltaTime);
}

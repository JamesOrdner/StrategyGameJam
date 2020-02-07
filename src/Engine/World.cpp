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

void World::destroyObject(class GameObject* object)
{
    destroyedObjects.emplace(object);
}

void World::tick(uint32_t deltaTime)
{
    for (auto& obj : objects) obj->tick(deltaTime);
    
    // remove all destroyed objects
    for (auto* deadObject : destroyedObjects) {
        for (auto it = objects.begin(); it != objects.end(); it++) {
            if (it->get() == deadObject) {
                objects.erase(it);
                break;
            }
        }
    }
    destroyedObjects.clear();
}

int World::getWidth()
{
    return width;
}

int World::getHeight()
{
    return height;
}

int World::getHalfWidth()
{
    return halfWidth;
}

int World::getHalfHeight()
{
    return halfHeight;
}

#include "World.hpp"
#include "Engine.hpp"
#include "GameState.hpp"
#include "GameObject.hpp"
#include "../Objects/Actor.hpp"
#include "../Objects/ResourcePoint.hpp"

World::World(const Engine* engine) :
    engine(engine)
{
    
}

World::~World()
{
    
}

ResourcePoint* World::spawnResourcePoint(ResourceType type)
{
    auto* ptr = objects.emplace_back(std::make_unique<ResourcePoint>(this, SDL_FPoint{}, type)).get();
    return static_cast<ResourcePoint*>(ptr);
}

void World::destroyObject(class GameObject* object)
{
    destroyedObjects.emplace(object);
    
    if (auto* actor = dynamic_cast<Actor*>(object)) {
        engine->gameStatePtr()->actorKilled(actor);
    }
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

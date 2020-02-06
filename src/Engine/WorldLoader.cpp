#include "WorldLoader.hpp"
#include "World.hpp"
#include "Engine.hpp"
#include "../Objects/Actor.hpp"

void WorldLoader::createWorld(const Engine* engine, World* world)
{
    createBuildings(world);
    /// createResources();
    /// createScenery();

}

void WorldLoader::createBuildings(World* world)
{
    for (int i=0; i<5; i++) {
        auto* myObject = world->spawnObject<DrawableObject>();
        myObject->position.x = rand()%200;
        myObject->position.y = rand()%200;
        myObject->setSprite(20,20,SDL_Color{rand()%255,rand()%255,rand()%255,230});
    }
}

void WorldLoader::createResources(World* world)
{
}

void WorldLoader::createScenery(World* world)
{
}


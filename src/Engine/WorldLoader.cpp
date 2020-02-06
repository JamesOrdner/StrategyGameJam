#include "WorldLoader.hpp"
#include "World.hpp"
#include "Engine.hpp"
#include "../Objects/Actor.hpp"
#include <random>


void WorldLoader::createWorld(const Engine* engine, World* world)
{

    createBuildings(world);
    /// createResources();
    /// createScenery();

}

int WorldLoader::getRandomInt()
{
    static std::random_device r;
    static std::default_random_engine randIntGenerator(r());
    static std::uniform_int_distribution<int> distribution(-255,255);

    return distribution(randIntGenerator);
}

void WorldLoader::createBuildings(World* world)
{
    auto* myObject = world->spawnObject<DrawableObject>();
    myObject->position.x = 0;
    myObject->position.y = 0;
    myObject->setSprite(20,20,SDL_Color{255,255,255,255});

    for (int i=0; i<5; i++) {
        auto* myObject = world->spawnObject<DrawableObject>();
        myObject->position.x = getRandomInt();
        myObject->position.y = getRandomInt();
        myObject->setSprite(20,20,SDL_Color{(uint8_t)getRandomInt(),(uint8_t)getRandomInt(),(uint8_t)getRandomInt(),255});
    }
    
    // yeettree
    auto* tree = world->spawnObject<DrawableObject>();
    tree->position = { 600, 0 };
    tree->setSprite("res/textures/world/tree_large_1.bmp");
    
    // yeetrock
    auto* rock = world->spawnObject<DrawableObject>();
    rock->position = { 600, 500 };
    rock->rotation = static_cast<double>(getRandomInt());
    rock->setSprite("res/textures/world/rock_medium_1.bmp");
    
    // yeetrock2000
    auto* rock2000 = world->spawnObject<DrawableObject>();
    rock2000->position = { 300, 400 };
    rock2000->rotation = -static_cast<double>(getRandomInt());
    rock2000->setSprite("res/textures/world/rock_medium_1.bmp");
}

void WorldLoader::createResources(World* world)
{
}

void WorldLoader::createScenery(World* world)
{
}


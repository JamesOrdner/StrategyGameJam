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

int WorldLoader::getRandomInt(int min, int max)
{
    static std::random_device r;
    static std::default_random_engine randIntGenerator(r());
    static std::uniform_int_distribution<int> distribution(min,max);

    return distribution(randIntGenerator);
}

int WorldLoader::getStructureOrigin()
{
    return 0;
}

int mapMinMax = 2000;
void WorldLoader::createBuildings(World* world)
{
    auto* enemyBase = world->spawnObject<DrawableObject>();
    enemyBase->position = {0,0};
    enemyBase->setSprite(1000,1000,SDL_Color{0, 100, 0, 255});

    for (int i=0; i<50; i++) {
        auto* myObject = world->spawnObject<DrawableObject>();
        myObject->position.x = getRandomInt(-world->getHalfWidth(), world->getHalfWidth());
        myObject->position.y = getRandomInt(-world->getHalfHeight(), world->getHalfHeight());
        myObject->rotation = static_cast<double>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth()));
        myObject->setSprite("res/textures/world/mushroom_small_1.bmp");
    }
    
    // yeettree
    for (int i=0; i<100; i++) {
        auto* tree = world->spawnObject<DrawableObject>();
        tree->position = { static_cast<float>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth())), static_cast<float>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth()))};
        tree->setRenderDepth(RenderDepth::Tree);
        tree->setSprite("res/textures/world/tree_large_1.bmp");
    }
    
    // yeetrock
    auto* rock = world->spawnObject<DrawableObject>();
    rock->position = { 600, 500 };
    rock->rotation = static_cast<double>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth()));
    rock->setSprite("res/textures/world/rock_medium_1.bmp");
    
    // yeetrock2000
    auto* rock2000 = world->spawnObject<DrawableObject>();
    rock2000->position = { 300, 400 };
    rock2000->rotation = -static_cast<double>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth()));
    rock2000->setSprite("res/textures/world/rock_medium_1.bmp");
    
    // structure
    auto* structure = world->spawnObject<Actor>();
    structure->position = { -500, -500};
    structure->setSprite(200, 200, SDL_Color{ 255, 255, 255, 255 });
    
    // yeetbruh
    auto* bruh = world->spawnObject<Actor>();
    bruh->position = { 0, 0};
    bruh->setSprite(2, 2, SDL_Color{ 255, 0, 0, 255 });
//    
//    // badbruh
//    auto* badbruh = world->spawnObject<Actor>();
//    badbruh->position = { -100, 1000 };
//    badbruh->setSprite(100, 100, SDL_Color{ 255, 0, 0, 255 });
//    badbruh->setTeam(Team::Enemy);
}

void WorldLoader::createResources(World* world)
{
}

void WorldLoader::createScenery(World* world)
{
}


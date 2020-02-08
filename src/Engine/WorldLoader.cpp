#include "WorldLoader.hpp"
#include "World.hpp"
#include "Engine.hpp"
#include "../Objects/Actor.hpp"
#include "../Objects/Structure.hpp"
#include "../Objects/DrawableObject.hpp"
#include <random>
#include <cmath>

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

int mapMinMax = 2000;
void WorldLoader::createBuildings(World* world)
{
    auto* enemyBase = world->spawnObject<DrawableObject>();
    enemyBase->setSprite(1000,1000,SDL_Color{0, 100, 0, 255});
    createStructureOrigin(world, enemyBase);

/*    for (int i=0; i<50; i++) {
        auto* myObject = world->spawnObject<DrawableObject>();
        myObject->position.x = getRandomInt(-world->getHalfWidth(), world->getHalfWidth());
        myObject->position.y = getRandomInt(-world->getHalfHeight(), world->getHalfHeight());
        myObject->rotation = static_cast<double>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth()));
        myObject->setSprite("res/textures/world/mushroom_small_1.bmp");
    }
    
    // yeettree
    for (int i=0; i<100; i++) {
        auto* tree = world->spawnObject<DrawableObject>();
        tree->position = { static_cast<float>(getRandomInt(-world->getWidth(), world->getWidth())), static_cast<float>(getRandomInt(-world->getHeight(), world->getHeight()))};
        tree->setRenderDepth(RenderDepth::Tree);
        tree->setSprite("res/textures/world/tree_large_1.bmp");
    }
    
    // yeetrock
    auto* rock = world->spawnObject<DrawableObject>({ 600, 500 });
    rock->rotation = static_cast<double>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth()));
    rock->setSprite("res/textures/world/rock_medium_1.bmp");
    
    // yeetrock2000
    auto* rock2000 = world->spawnObject<DrawableObject>({ 300, 400 });
    rock2000->rotation = -static_cast<double>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth()));
    rock2000->setSprite("res/textures/world/rock_medium_1.bmp");
    
    // structure
    auto* structure = world->spawnObject<Structure>({ -500, -500 });
    structure->setSprite(200, 200, SDL_Color{ 255, 255, 255, 255 });
    
    // yeetbruh
    auto* bruh = world->spawnObject<Actor>({ 0, 0 });
    bruh->setSprite("res/textures/world/tree_large_1.bmp");
    
    auto* breh = world->spawnObject<Actor>({ 500, 0 });
    breh->setSprite("res/textures/world/tree_large_1.bmp");
    
    // badbruh
    auto* badbruh = world->spawnObject<Actor>({ -100, 1000 });
    badbruh->setSprite(100, 100, SDL_Color{ 255, 0, 0, 255 });
    badbruh->setTeam(Team::Enemy);
*/
}

void WorldLoader::createResources(World* world)
{
}

void WorldLoader::createScenery(World* world)
{
}

std::vector<DrawableObject> WorldLoader::createdStructures;
void WorldLoader::createStructureOrigin(World* world, DrawableObject* newStructure)
{
    SDL_FPoint randomOrigin = { static_cast<float>(getRandomInt(-world->getWidth(), world->getWidth())), static_cast<float>(getRandomInt(-world->getHeight(), world->getHeight()))};

    for (int i=0; i<createdStructures.size(); i++) {
        DrawableObject* exisitingStructure = &(createdStructures[i]);
        newStructure->position = randomOrigin;

        if (isTooClose( newStructure, exisitingStructure)) {
            randomOrigin = { static_cast<float>(getRandomInt(-world->getWidth(), world->getWidth())), static_cast<float>(getRandomInt(-world->getHeight(), world->getHeight()))};
            i=0;
        }
    }
}

bool WorldLoader::isTooClose(DrawableObject* newStructure, DrawableObject* existingStructure) {
    float newStructureRadius = getRadius(newStructure);

    return true;
}

float WorldLoader::getRadius(DrawableObject* structure) {
    return sqrt(pow(structure->bounds.value().x,2) + pow(structure->bounds.value().y,2));
}


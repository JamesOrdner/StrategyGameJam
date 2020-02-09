#include "WorldLoader.hpp"
#include "World.hpp"
#include "Engine.hpp"
#include "../Objects/Actor.hpp"
#include "../Objects/Structure.hpp"
#include "../Objects/DrawableObject.hpp"
#include "../Objects/ResourcePoint.hpp"
#include "../Util/SDLMath.hpp"
#include <random>
#include <cmath>


void WorldLoader::createWorld(const Engine* engine, World* world)
{
    createStructures(world);
    createScenery(world);
}

int WorldLoader::getRandomInt(int min, int max)
{
    static std::random_device r;
    static std::default_random_engine randIntGenerator(r());
    static std::uniform_int_distribution<int> distribution(min,max);

    return distribution(randIntGenerator);
}

const int WorldLoader::minDistanceBetweenStructures;
void WorldLoader::createStructures(World* world)
{
    auto* enemyBase = world->spawnObject<DrawableObject>({0,0});
    //enemyBase->setSprite(1000,1000,SDL_Color{0, 100, 0, 255});
    enemyBase->setSprite("res/textures/world/enemy_base.bmp");
    createdStructures.push_back(enemyBase);

    auto* wood = world->spawnResourcePoint(ResourceType::Wood);
    createStructureOrigin(world, wood, minDistanceBetweenStructures);
    createdStructures.push_back(wood);
    
    auto* iron = world->spawnResourcePoint(ResourceType::Iron);
    createStructureOrigin(world, iron, minDistanceBetweenStructures);
    createdStructures.push_back(iron);
    
    auto* crystal = world->spawnResourcePoint(ResourceType::Crystal);
    createStructureOrigin(world, crystal, minDistanceBetweenStructures);
    createdStructures.push_back(crystal);
    
    auto* wolf = world->spawnResourcePoint(ResourceType::Wolf);
    createStructureOrigin(world, wolf, minDistanceBetweenStructures);
    createdStructures.push_back(wolf); 
}

const int WorldLoader::minDistanceFromStructures;
void WorldLoader::createScenery(World* world)
{
    int numTrees = 200;
    int numRocks = 50;
    int numMushrooms = 500;

    // Trees
    for (int i=0; i<numTrees; i++) {
        auto* tree = world->spawnObject<DrawableObject>();
        tree->position.x = getRandomInt(-world->getHalfWidth(), world->getHalfWidth());
        tree->position.y = getRandomInt(-world->getHalfHeight(), world->getHalfHeight());
        tree->rotation = static_cast<double>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth()));
        tree->setSprite("res/textures/world/tree_large_1.bmp");
        createStructureOrigin(world, tree, minDistanceFromStructures); 
    }
    
    for (int i=0; i<numRocks; i++) {
        auto* rock = world->spawnObject<DrawableObject>();
        rock->position.x = getRandomInt(-world->getHalfWidth(), world->getHalfWidth());
        rock->position.y = getRandomInt(-world->getHalfHeight(), world->getHalfHeight());
        rock->rotation = static_cast<double>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth()));
        rock->setSprite("res/textures/world/rock_medium_1.bmp");
        createStructureOrigin(world, rock, minDistanceFromStructures); 
    }

    for (int i=0; i<numMushrooms; i++) {
        auto* mushroom = world->spawnObject<DrawableObject>();
        mushroom->position.x = getRandomInt(-world->getHalfWidth(), world->getHalfWidth());
        mushroom->position.y = getRandomInt(-world->getHalfHeight(), world->getHalfHeight());
        mushroom->rotation = static_cast<double>(getRandomInt(-world->getHalfWidth(), world->getHalfWidth()));
        mushroom->setSprite("res/textures/world/mushroom_small_1.bmp");
        createStructureOrigin(world, mushroom, minDistanceFromStructures);
    }
    
}

std::vector<DrawableObject*> WorldLoader::createdStructures;
void WorldLoader::createStructureOrigin(World* world, DrawableObject* newStructure, int minDistance)
{
    SDL_FPoint randomOrigin = { static_cast<float>(getRandomInt(-world->getWidth(), world->getWidth())), static_cast<float>(getRandomInt(-world->getHeight(), world->getHeight()))};
    //printf("Origin: (%f,%f)\n", randomOrigin.x, randomOrigin.y);
    newStructure->position = randomOrigin;
    for (int i=0; i<createdStructures.size(); i++) {
        DrawableObject* exisitingStructure = createdStructures[i];
        newStructure->position = randomOrigin;

        if (isTooClose( newStructure, exisitingStructure, minDistance)) {
            randomOrigin = { static_cast<float>(getRandomInt(-world->getWidth(), world->getWidth())), static_cast<float>(getRandomInt(-world->getHeight(), world->getHeight()))};
            i=0;
            printf("If this don't stop it's an infinite loop\n");
        }
    }
}

bool WorldLoader::isTooClose(DrawableObject* newStructure, DrawableObject* existingStructure, int minDistanceLimit) {
    float distanceBetweenStructures = dist(newStructure->position, existingStructure->position);

    return minDistanceLimit > distanceBetweenStructures; //getRadius(newStructure)+getRadius(existingStructure);
}

float WorldLoader::getRadius(DrawableObject* structure) {
    return sqrt(pow(structure->bounds.value().x,2) + pow(structure->bounds.value().y,2));
}


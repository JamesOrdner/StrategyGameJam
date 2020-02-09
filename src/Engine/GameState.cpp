#include "GameState.hpp"
#include "Engine.hpp"
#include "WorldLoader.hpp"
#include "ActorFactory.hpp"
#include "../Objects/Actor.hpp"
#include "../Objects/ResourcePoint.hpp"
#include <algorithm>
#include <random>

GameState::GameState(const Engine* engine) :
    engine(engine),
    money(0),
    moneyTimer(0),
    resourceTimer(0),
    enemyTimer(0),
    spawnTime(3000),
    resources{}
{
    
}

void GameState::startGame()
{
    WorldLoader::createWorld(engine, engine->activeWorld());
    
    // select starting base
    static std::random_device r;
    static std::default_random_engine randomGenerator(r());
    static std::uniform_int_distribution<int> distribution(0, 3);
    switch (distribution(randomGenerator)) {
        case 0: resources.wood.bOwned    = true; break;
        case 1: resources.iron.bOwned    = true; break;
        case 2: resources.crystal.bOwned = true; break;
        case 3: resources.wolf.bOwned    = true; break;
    }
}

void GameState::tick(uint32_t deltaTime)
{
    resourceTimer += deltaTime;
    while (resourceTimer >= 1000) {
        resources.addResouces(1);
        resourceTimer -= 1000;
    }
    
    moneyTimer += deltaTime;
    while (moneyTimer >= 2000) {
        money++;
        moneyTimer -= 2000;
    }

    enemyTimer += deltaTime;
    if (enemyTimer >= spawnTime) {
        auto* badbruh = engine->activeWorld()->spawnObject<Actor>({0,0});
        badbruh->setSprite("res/textures/world/enemy.bmp");
        badbruh->setTeam(Team::Enemy);
        enemyTimer -= spawnTime;
    }
}

void GameState::setResourcePoint(class ResourcePoint* point, ResourceType type)
{
    switch (type) {
        case ResourceType::Wood:
            resources.wood.resourcePoint = point;
            break;
        case ResourceType::Iron:
            resources.iron.resourcePoint = point;
            break;
        case ResourceType::Crystal:
            resources.crystal.resourcePoint = point;
            break;
        case ResourceType::Wolf:
            resources.wolf.resourcePoint = point;
            break;
    }
}

void GameState::actorSelected(Actor* actor, bool bMultiSelect, bool bCommand)
{
    if (bCommand) {
        if (actor->team() == Team::Enemy) {
            for (auto& selectedActor : selectedActors) selectedActor->setTarget(actor);
        }
    }
    else { // selection
        if (actor->team() == Team::Player) {
            if (!bMultiSelect) {
                for (auto& selectedActor : selectedActors) selectedActor->setSelected(false);
                selectedActors.clear();
            }
            selectedActors.push_back(actor);
            actor->setSelected(true);
        }
    }
}

void GameState::terrainSelected(const SDL_Point& position, bool bCommand)
{
    if (bCommand) {
        for (auto& actor : selectedActors) {
            SDL_FPoint dest{ static_cast<float>(position.x), static_cast<float>(position.y) };
            actor->setDestination(dest);
        }
    }
    else {
        for (auto& actor : selectedActors) actor->setSelected(false);
        selectedActors.clear();
    }
}

void GameState::actorKilled(Actor* actor)
{
    auto deleteIter = std::remove(selectedActors.begin(), selectedActors.end(), actor);
    if (deleteIter != selectedActors.end()) selectedActors.erase(deleteIter);
    
    if (actor->team() == Team::Enemy) {
        money += actor->getKillValue();
    }
    
    if (auto* respt = dynamic_cast<ResourcePoint*>(actor)) {
        switch(respt->resource) {
            case ResourceType::Wood:
                resources.wood = {};
                break;
            case ResourceType::Iron:
                resources.iron = {};
                break;
            case ResourceType::Crystal:
                resources.crystal = {};
                break;
            case ResourceType::Wolf:
                resources.wolf = {};
                break;
        }
    }
}

int GameState::getResourceCount(ResourceType resouce) const
{
    switch (resouce) {
        case ResourceType::Wood:    return resources.wood.value;
        case ResourceType::Iron:    return resources.iron.value;
        case ResourceType::Crystal: return resources.crystal.value;
        case ResourceType::Wolf:    return resources.wolf.value;
    }
}

bool GameState::isUnitBuildable(PlayerUnit unit) const
{
    return
        (resources.wood.value    >= ActorFactory::unitCost(unit, ResourceType::Wood)) &&
        (resources.iron.value    >= ActorFactory::unitCost(unit, ResourceType::Iron)) &&
        (resources.crystal.value >= ActorFactory::unitCost(unit, ResourceType::Crystal)) &&
        (resources.wolf.value    >= ActorFactory::unitCost(unit, ResourceType::Wolf));
}

bool GameState::buildUnit(PlayerUnit unit)
{
    if (!isUnitBuildable(unit)) return false;
    resources.wood.value    -= ActorFactory::unitCost(unit, ResourceType::Wood);
    resources.iron.value    -= ActorFactory::unitCost(unit, ResourceType::Iron);
    resources.crystal.value -= ActorFactory::unitCost(unit, ResourceType::Crystal);
    resources.wolf.value    -= ActorFactory::unitCost(unit, ResourceType::Wolf);
    
    // resource base location
    SDL_FPoint spawnLoc;
    switch (ActorFactory::unitSpawnLocation(unit)) {
        case ResourceType::Wood:
            spawnLoc = resources.wood.resourcePoint->position;
            break;
        case ResourceType::Iron:
            spawnLoc = resources.iron.resourcePoint->position;
            break;
        case ResourceType::Crystal:
            spawnLoc = resources.crystal.resourcePoint->position;
            break;
        case ResourceType::Wolf:
            spawnLoc = resources.wolf.resourcePoint->position;
            break;
    }
    
    ActorFactory::spawnUnit(engine->activeWorld(), unit, spawnLoc);
    return true;
}

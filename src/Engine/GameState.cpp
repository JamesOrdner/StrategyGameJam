#include "GameState.hpp"
#include "Engine.hpp"
#include "WorldLoader.hpp"
#include "ActorFactory.hpp"
#include "../AI/AIComponent.hpp"
#include "../Objects/Actor.hpp"
#include "../Objects/ResourcePoint.hpp"
#include <algorithm>
#include <random>

GameState::GameState(const Engine* engine) :
    engine(engine),
    unitMoneyCost(5),
    money(0),
    moneyTimer(0),
    resourceTimer(0),
    enemyTimer(0),
    spawnTime(10000),
    resources{}
{
    
}

void GameState::Resources::addResouces(int amount) {
    if (wood.resourcePoint &&
        wood.resourcePoint->aiComponent->team == Team::Player) wood.value += amount;
    if (iron.resourcePoint &&
        iron.resourcePoint->aiComponent->team == Team::Player) iron.value += amount;
    if (crystal.resourcePoint &&
        crystal.resourcePoint->aiComponent->team == Team::Player) crystal.value += amount;
    if (wolf.resourcePoint &&
        wolf.resourcePoint->aiComponent->team == Team::Player) wolf.value += amount;
}

void GameState::startGame()
{
    WorldLoader::createWorld(engine, engine->activeWorld());
    
    // select starting base
    static std::random_device r;
    static std::default_random_engine randomGenerator(r());
    static std::uniform_int_distribution<int> distribution(0, 3);
    switch (distribution(randomGenerator)) {
        case 0:
            resources.wood.resourcePoint->aiComponent->team = Team::Player;
            break;
        case 1:
            resources.iron.resourcePoint->aiComponent->team = Team::Player;
            break;
        case 2:
            resources.crystal.resourcePoint->aiComponent->team = Team::Player;
            break;
        case 3:
            resources.wolf.resourcePoint->aiComponent->team = Team::Player;
            break;
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

    static int numEnemies = 0;
    enemyTimer += deltaTime;
    if (enemyTimer >= spawnTime) {
        auto* badbruh = engine->activeWorld()->spawnObject<Actor>({0,0});
        badbruh->setSprite("res/textures/world/enemy.bmp");
        badbruh->aiComponent->team = Team::Enemy;

        printf("\ndelta time: %d\n", deltaTime);
        printf("enemy time: %d\n", enemyTimer);
        printf("spawn time: %d\n", spawnTime);
        
        numEnemies += 1;
        if (numEnemies % 6 == 0 && numEnemies <= 30) {
            spawnTime -= 1500;
            badbruh->aiComponent->movementSpeed *= 5;
        }

        enemyTimer = 0;
    }
}

void GameState::setResourcePoint(ResourcePoint* point, ResourceType type)
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
        if (actor->aiComponent->team == Team::Enemy) {
            for (auto& selectedActor : selectedActors) selectedActor->aiComponent->setTarget(actor);
        }
        else if (dynamic_cast<ResourcePoint*>(actor) && actor->aiComponent->team == Team::None) {
            for (auto& selectedActor : selectedActors) selectedActor->aiComponent->setTarget(actor);
        }
    }
    else { // selection
        if (actor->aiComponent->team == Team::Player) {
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
            actor->aiComponent->setDestination(dest);
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
    
    if (actor->aiComponent->team == Team::Enemy) {
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
        (money >= unitMoneyCost) &&
        (resources.wood.value    >= ActorFactory::unitCost(unit, ResourceType::Wood)) &&
        (resources.iron.value    >= ActorFactory::unitCost(unit, ResourceType::Iron)) &&
        (resources.crystal.value >= ActorFactory::unitCost(unit, ResourceType::Crystal)) &&
        (resources.wolf.value    >= ActorFactory::unitCost(unit, ResourceType::Wolf)) ;
}

bool GameState::buildUnit(PlayerUnit unit)
{
    if (!isUnitBuildable(unit)) return false;
    money -= unitMoneyCost;
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

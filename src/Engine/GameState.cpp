#include "GameState.hpp"
#include "Engine.hpp"
#include "WorldLoader.hpp"
#include "ActorFactory.hpp"
#include "../Objects/Actor.hpp"
#include "../Objects/ResourcePoint.hpp"

GameState::GameState(const Engine* engine) :
    engine(engine),
    money(0),
    resources{}
{
    
}

void GameState::startGame()
{
    WorldLoader::createWorld(engine, engine->activeWorld());
}

void GameState::setResourcePoint(class ResourcePoint* point, ResourceType type)
{
    switch (type) {
        case ResourceType::Wood:    resources.wood.resourcePoint = point;
        case ResourceType::Iron:    resources.iron.resourcePoint = point;
        case ResourceType::Crystal: resources.crystal.resourcePoint = point;
        case ResourceType::Wolf:    resources.wolf.resourcePoint = point;
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
            case ResourceType::Wood:    resources.wood = {};
            case ResourceType::Iron:    resources.iron = {};
            case ResourceType::Crystal: resources.crystal = {};
            case ResourceType::Wolf:    resources.wolf = {};
        }
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
        case ResourceType::Wood:    spawnLoc = resources.wood.resourcePoint->position;
        case ResourceType::Iron:    spawnLoc = resources.iron.resourcePoint->position;
        case ResourceType::Crystal: spawnLoc = resources.crystal.resourcePoint->position;
        case ResourceType::Wolf:    spawnLoc = resources.wolf.resourcePoint->position;
    }
    
    ActorFactory::spawnUnit(engine->activeWorld(), unit, spawnLoc);
    return true;
}

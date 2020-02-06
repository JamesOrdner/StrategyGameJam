#include "GameState.hpp"
#include "Engine.hpp"
#include "WorldLoader.hpp"

GameState::GameState(const Engine* engine) :
    engine(engine),
    money(0)
{
    
}

void GameState::startGame()
{
    // load world
    WorldLoader::createWorld(engine, engine->activeWorld());

    // start game
}

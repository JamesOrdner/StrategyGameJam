#include "GameState.hpp"
#include "Engine.hpp"
#include "WorldLoader.hpp"

GameState::GameState(const Engine* engine) :
    money(0),
    engine(engine)
{
    
}

void GameState::startGame()
{
    // load world
    WorldLoader::createWorld(engine, engine->activeWorld());

    // start game
}

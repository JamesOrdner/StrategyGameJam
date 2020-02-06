#ifndef GameState_hpp
#define GameState_hpp

#include <vector>

class GameState
{
public:
    
    GameState(const class Engine* engine);
    
    void startGame();
    
    std::vector<class Actor*> selectedActors;
    
private:
    
    const class Engine* const engine;

    unsigned int money;
};

#endif /* GameState_hpp */

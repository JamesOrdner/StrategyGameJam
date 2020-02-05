#ifndef GameState_hpp
#define GameState_hpp

#include <vector>

class GameState
{
public:
    
    GameState();
    
    void startGame();
    
    std::vector<class Actor*> selectedActors;
    
private:
    
    unsigned int money;
};

#endif /* GameState_hpp */

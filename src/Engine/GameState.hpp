#ifndef GameState_hpp
#define GameState_hpp

#include <SDL_rect.h>
#include <vector>

class GameState
{
public:
    
    GameState(const class Engine* engine);
    
    void startGame();
    
    /// bMultiSelect == true if modifier key like shift is held
    void actorSelected(class Actor* actor, bool bMultiSelect);
    
    /// bCommand == true when right click (command), false if left click (deselection)
    void terrainSelected(const SDL_Point& position, bool bCommand);
    
private:
    
    const class Engine* const engine;
    
    std::vector<class Actor*> selectedActors;
    
    unsigned int money;
};

#endif /* GameState_hpp */

#ifndef GameState_hpp
#define GameState_hpp

#include <SDL_rect.h>
#include <vector>

class GameState
{
public:
    
    GameState(const class Engine* engine);
    
    void startGame();
    
    /// bMultiSelect == true if modifier key like shift is held.
    /// bCommand == true when right click (command), false if left click (selection)
    void actorSelected(class Actor* actor, bool bMultiSelect, bool bCommand);
    
    /// bCommand == true when right click (command), false if left click (selection)
    void terrainSelected(const SDL_Point& position, bool bCommand);
    
    void actorKilled(class Actor* actor);
    
    inline unsigned int getMoney() const { return money; }
    
private:
    
    const class Engine* const engine;
    
    std::vector<class Actor*> selectedActors;
    
    unsigned int money;
};

#endif /* GameState_hpp */

#ifndef Input_hpp
#define Input_hpp

#include "../Engine/GameSystem.hpp"
#include "InputTypes.hpp"
#include <SDL_events.h>
#include <unordered_set>

class Input : public GameSystem
{
public:
    
    Input(const class Engine* engine);
    
    ~Input();
    
    /// Process input and call required callbacks on InputComponents.
    /// Returns true during normal operation, false if game quit was requested.
    bool execute(uint32_t deltaTime) override;
    void registerComponent(class GameObjectComponent* component) override;
    void unregisterComponent(class GameObjectComponent* component) override;
    
    /// Pointer to UI system
    class UI* ui;
    
private:
    
    /// All registered input components
    std::unordered_set<class InputComponent*> inputComponents;
    
    /// Call the registered callbacks (if any) for the given event
    void execCallback(InputEvent event, float value);
    
    void processPrimaryClick(const SDL_Event& event);
    
    void processSecondaryClick(const SDL_Event& event);
    
    void processKeyEvent(const SDL_Event& event);
};

#endif /* Input_hpp */

#ifndef Input_hpp
#define Input_hpp

#include "../Engine/GameSystem.hpp"
#include "InputTypes.hpp"
#include <vector>

class Input : public GameSystem
{
public:
    
    Input();
    
    ~Input();
    
    /// Process input and call required callbacks on InputComponents.
    /// Returns true during normal operation, false if game quit was requested.
    bool execute(uint32_t deltaTime) override;
    
private:
    
    // All registered input components
    std::vector<class InputComponent*> inputComponents;
    
    // Call the registered callbacks (if any) for the given event
    void execCallback(InputEvent event, float value);
    
    void processKeyEvent(const union SDL_Event& event);
    
};

#endif /* Input_hpp */

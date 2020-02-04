#ifndef InputComponent_hpp
#define InputComponent_hpp

#include "../Engine/GObjectComponent.hpp"
#include "InputTypes.hpp"
#include <map>

class InputComponent : public GObjectComponent
{
public:
    
    /// Execute the callback for an event, called directly from the Input system
    void executeEvent(InputEvent event, float value);
    
    /// Register a callback for the given event, replacing any existing callback for the event
    void registerEvent(InputEvent event, InputCallback callback);
    
    /// Remove the callback for the given event
    void unregisterEvent(InputEvent event);
    
private:
    
    std::map<InputEvent, InputCallback> callbacks;
};

#endif /* InputComponent_hpp */

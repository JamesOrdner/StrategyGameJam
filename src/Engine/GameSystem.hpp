#ifndef GameSystem_hpp
#define GameSystem_hpp

#include <cstdint>

/// GameSystem is an abstract class which is implemented by all
/// game systems, such as Input, Graphics, AI, etc.
class GameSystem
{
public:
    
    GameSystem(const class Engine* engine) : engine(engine) {}
    
    virtual ~GameSystem() {};
    
    /// Called during engine startup
    virtual void init() {};
    
    /// Called during engine shutdown
    virtual void deinit() {};
    
    /// Register a component with this system
    virtual void registerComponent(class GameObjectComponent* component) = 0;
    
    /// Unregister a component from this system
    virtual void unregisterComponent(class GameObjectComponent* component) = 0;
    
    /// Called each frame, with the number of ms since the last frame.
    /// Returns true during normal operation.
    virtual bool execute(uint32_t deltaTime) = 0;
    
protected:
    
    const class Engine* const engine;
};

#endif /* GameSystem_hpp */

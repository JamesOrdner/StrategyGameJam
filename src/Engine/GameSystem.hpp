#ifndef GameSystem_hpp
#define GameSystem_hpp

#include <cstdint>

/// GameSystem is an abstract class which is implemented by all
/// game systems, such as Input, Graphics, AI, etc.
class GameSystem
{
public:
    
    /// Called during engine startup
    virtual void init() {};
    
    /// Called during engine shutdown
    virtual void deinit() {};
    
    /// Called each frame, with the number of ms since the last frame.
    /// Returns true during normal operation.
    virtual bool execute(uint32_t deltaTime) = 0;
};

#endif /* GameSystem_hpp */

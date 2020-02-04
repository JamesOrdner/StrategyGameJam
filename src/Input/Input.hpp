#ifndef Input_hpp
#define Input_hpp

#include "../Engine/GameSystem.hpp"
#include "InputTypes.hpp"

class Input : public GameSystem
{
public:
    
    Input();
    
    ~Input();
    
    /// Process input and call required callbacks on InputComponents.
    /// Returns true during normal operation, false if game quit was requested.
    bool execute(uint32_t deltaTime) override;
    
};

#endif /* Input_hpp */

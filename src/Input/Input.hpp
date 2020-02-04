#ifndef Input_hpp
#define Input_hpp

#include "InputTypes.hpp"

class Input
{
public:
    
    Input();
    
    ~Input();
    
    /// Process input and call required callbacks on InputComponents.
    /// Returns true during normal operation, false if game quit was requested.
    bool processInput();
    
};

#endif /* Input_hpp */

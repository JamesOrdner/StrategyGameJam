#ifndef ResourcePoint_hpp
#define ResourcePoint_hpp

#include "Structure.hpp"

class ResourcePoint : public Structure
{
public:
    
    ResourcePoint(class World* world, const SDL_FPoint& position, ResourceType resource);
    
    const ResourceType resource;
    
    /// Subtract deltaTimeWaited from remaining capture time, return true if captured
    bool waitCapture(uint32_t deltaTimeWaited);
    
private:
    
    /// Remaining time (ms) to capture
    uint32_t captureTime;
};

#endif /* ResourcePoint_hpp */

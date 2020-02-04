#ifndef GWorld_hpp
#define GWorld_hpp

#include <vector>
#include <memory>

class GWorld
{
public:
    
    GWorld();
    
    ~GWorld();
    
private:
    
    std::vector<std::unique_ptr<class GObject>> objects;
};

#endif /* GWorld_hpp */

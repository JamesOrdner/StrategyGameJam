#ifndef GObject_hpp
#define GObject_hpp

#include <vector>
#include <memory>

class GObject
{
public:
    
    GObject();
    
    ~GObject();
    
private:
    
    std::vector<std::unique_ptr<class GObjectComponent>> components;
};

#endif /* GObject_hpp */

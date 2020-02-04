#ifndef Engine_hpp
#define Engine_hpp

#include <vector>
#include <memory>

class Engine
{
public:
    
    Engine();
    
    ~Engine();
    
    void init();
    
    void deinit();
    
    void run();
    
private:
    
    std::vector<std::unique_ptr<class GWorld>> worlds;
    
    std::unique_ptr<class Renderer> renderer;
    
    std::unique_ptr<class Input> input;
};

#endif /* Engine_hpp */

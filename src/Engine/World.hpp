#ifndef GWorld_hpp
#define GWorld_hpp

#include <vector>
#include <memory>

class World
{
public:
    
    World(const class Engine* engine);
    
    ~World();
    
    template<typename T>
    T* spawnObject() {
        auto* ptr = objects.emplace_back(std::make_unique<T>(engine)).get();
        return static_cast<T*>(ptr);
    }
    
    /// Called each frame, with the number of ms since the last frame
    void tick(uint32_t deltaTime);
    
private:
    
    const class Engine* const engine;
    
    std::vector<std::unique_ptr<class GameObject>> objects;
};

#endif /* GWorld_hpp */

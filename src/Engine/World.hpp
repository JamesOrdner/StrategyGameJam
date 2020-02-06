#ifndef GWorld_hpp
#define GWorld_hpp

#include <vector>
#include <memory>
#include <set>

class World
{
public:
    
    World(const class Engine* engine);
    
    ~World();
    
    template<typename T>
    T* spawnObject() {
        auto* ptr = objects.emplace_back(std::make_unique<T>(this)).get();
        return static_cast<T*>(ptr);
    }
    
    void destroyObject(class GameObject* object);
    
    /// Called each frame, with the number of ms since the last frame
    void tick(uint32_t deltaTime);
    
    const class Engine* const engine;
    
private:
    
    std::vector<std::unique_ptr<class GameObject>> objects;
    
    /// Keeps track of destroyed objects, which will be removed at some point
    std::set<class GameObject*> destroyedObjects;
};

#endif /* GWorld_hpp */

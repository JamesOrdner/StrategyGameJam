#ifndef GObject_hpp
#define GObject_hpp

#include "Engine.hpp"
#include <vector>
#include <memory>
#include <SDL_rect.h>

class GameObject
{
public:
    
    GameObject(const class Engine* engine);
    
    virtual ~GameObject();
    
    /// Creates an object component and registers it with the corresponding system.
    /// Returns an unowned pointer to the created component, which may be discarded.
    template<typename T>
    T* createComponent() {
        auto* ptr = components.emplace_back(engine->createComponent<T>(this)).get();
        return static_cast<T*>(ptr);
    }
    
    /// Called each frame, with the time since the last frame (ms)
    virtual void tick(uint32_t deltaTime) {};

    /// Position of the object
    SDL_FPoint position;
    
    /// Rotation of the object in degrees
    double rotation;
    
protected:
    
    const class Engine* const engine;

private:
    
    std::vector<std::unique_ptr<class GameObjectComponent>> components;
};

#endif /* GObject_hpp */

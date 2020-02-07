#ifndef GObject_hpp
#define GObject_hpp

#include "World.hpp"
#include "Engine.hpp"
#include <SDL_rect.h>
#include <vector>
#include <memory>
#include <optional>

class GameObject
{
public:
    
    GameObject(class World* world, const SDL_FPoint& position);
    
    virtual ~GameObject();
    
    /// Creates an object component and registers it with the corresponding system.
    /// Returns an unowned pointer to the created component, which may be discarded.
    template<typename T>
    T* createComponent() {
        auto* ptr = components.emplace_back(world->engine->createComponent<T>(this)).get();
        return static_cast<T*>(ptr);
    }
    
    /// Called each frame, with the time since the last frame (ms)
    virtual void tick(uint32_t deltaTime) {};
    
    /// Position of the object
    SDL_FPoint position;
    
    /// Bounds of the object, used for collision, selection, etc.
    /// May be set manually, but will be overridden if a sprite is loaded.
    std::optional<SDL_Point> bounds;
    
    /// Rotation of the object in degrees
    double rotation;
    
protected:
    
    class World* const world;

private:
    
    std::vector<std::unique_ptr<class GameObjectComponent>> components;
};

#endif /* GObject_hpp */

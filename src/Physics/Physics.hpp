#ifndef Physics_hpp
#define Physics_hpp

#include "../Engine/GameSystem.hpp"
#include <SDL_rect.h>
#include <vector>

class Physics : public GameSystem
{
public:
    
    Physics(const class Engine* engine);
    
    bool execute(uint32_t deltaTime) override;
    void registerComponent(class GameObjectComponent* component) override;
    void unregisterComponent(class GameObjectComponent* component) override;
    
    /// Returns the GameObject at the given world coordinates, or nullptr if failed
    class GameObject* objectAt(const SDL_Point& coords) const;
    
    bool colliding(const class GameObject* a, const class GameObject* b) const;
    
private:
    
    /// All registered Physics components
    std::vector<class PhysicsComponent*> physicsComponents;
    
    SDL_FPoint getForce(const class PhysicsComponent* component) const;
    
    /// World-space bounding box
    SDL_Rect objectWorldBounds(const class GameObject* object) const;
};

#endif /* Physics_hpp */

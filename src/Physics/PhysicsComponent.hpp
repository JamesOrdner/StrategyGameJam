#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include "../Engine/GameObjectComponent.hpp"

enum class PhysicsType
{
    Static,
    Actor,
    None
};

class PhysicsComponent : public GameObjectComponent
{
public:
    
    PhysicsComponent(class GameObject* owner);
    
    PhysicsType physicsType;
};

#endif /* PhysicsComponent_hpp */

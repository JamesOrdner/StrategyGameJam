#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include "../Engine/GameObjectComponent.hpp"
#include <SDL_rect.h>

class PhysicsComponent : public GameObjectComponent
{
public:
    
    PhysicsComponent(class GameObject* owner);
    
    SDL_Rect bounds;
};

#endif /* PhysicsComponent_hpp */

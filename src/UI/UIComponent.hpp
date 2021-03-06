#ifndef UIComponent_hpp
#define UIComponent_hpp

#include "../Engine/GameObjectComponent.hpp"
#include <SDL_rect.h>

class UIComponent : public GameObjectComponent
{
public:
    
    UIComponent(class GameObject* owner);
    
    bool bSelected;
};

#endif /* UIComponent_hpp */

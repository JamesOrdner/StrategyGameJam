#ifndef UIComponent_hpp
#define UIComponent_hpp

#include "../Engine/GameObjectComponent.hpp"

class UIComponent : public GameObjectComponent
{
public:
    
    UIComponent(class GameObject* owner);
};

#endif /* UIComponent_hpp */

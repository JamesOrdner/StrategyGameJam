#include "UIComponent.hpp"

UIComponent::UIComponent(class GameObject* owner) :
    GameObjectComponent(owner),
    bSelected(false),
    outlineBounds{}
{
}

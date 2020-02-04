#include "GameObjectComponent.hpp"

GameObjectComponent::GameObjectComponent(class GameObject* owner) :
    owner(owner)
{
}

GameObjectComponent::~GameObjectComponent()
{
}

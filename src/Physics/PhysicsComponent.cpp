#include "PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(class GameObject* owner) :
    GameObjectComponent(owner),
    physicsType(PhysicsType::Static)
{
}

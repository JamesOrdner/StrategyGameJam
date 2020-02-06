#include "GameObject.hpp"
#include "GameObjectComponent.hpp"
#include "World.hpp"
#include "Engine.hpp"

GameObject::GameObject(World* world) :
    position{},
    rotation(0),
    world(world)
{
}

GameObject::~GameObject()
{
    for (const auto& comp : components) {
        world->engine->unregisterComponent(comp.get());
    }
}

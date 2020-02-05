#include "GameObject.hpp"
#include "GameObjectComponent.hpp"
#include "Engine.hpp"

GameObject::GameObject(const Engine* engine) :
    position{},
    rotation(0),
    engine(engine)
{
}

GameObject::~GameObject()
{
    for (const auto& comp : components) {
        engine->unregisterComponent(comp.get());
    }
}

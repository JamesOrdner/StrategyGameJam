#include "GameObject.hpp"
#include "GameObjectComponent.hpp"
#include "Engine.hpp"

GameObject::GameObject(const Engine* engine) :
    engine(engine),
    position{}
{
}

GameObject::~GameObject()
{
    for (const auto& comp : components) {
        engine->unregisterComponent(comp.get());
    }
}

SDL_FPoint GameObject::getPosition() {  return position;  }


#include "GObject.hpp"
#include "GObjectComponent.hpp"
#include "Engine.hpp"

GObject::GObject(const Engine* engine) :
    engine(engine)
{
}

GObject::~GObject()
{
    for (const auto& comp : components) {
        engine->unregisterComponent(comp.get());
    }
}

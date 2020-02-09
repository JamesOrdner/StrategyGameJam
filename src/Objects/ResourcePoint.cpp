#include "ResourcePoint.hpp"
#include "../AI/AIComponent.hpp"

ResourcePoint::ResourcePoint(class World* world, const SDL_FPoint& position, ResourceType resource) :
    Structure(world, position),
    resource(resource),
    captureTime(15 * 1000)
{
    switch (resource) {
        case ResourceType::Wood:
            setSprite("res/textures/world/wood_source.bmp");
            break;
        case ResourceType::Iron:
            setSprite("res/textures/world/iron_cave.bmp");
            break;
        case ResourceType::Crystal:
            setSprite("res/textures/world/crystal.bmp");
            break;
        case ResourceType::Wolf:
            setSprite("res/textures/world/wolf_source.bmp");
            break;
    }
    
    aiComponent->team = Team::None;
}

bool ResourcePoint::waitCapture(uint32_t deltaTimeWaited)
{
    if (captureTime <= deltaTimeWaited) {
        captureTime = 0;
        return true;
    }
    else {
        captureTime -= deltaTimeWaited;
        return false;
    }
}

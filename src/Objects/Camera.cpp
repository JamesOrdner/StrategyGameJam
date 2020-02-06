#include "Camera.hpp"
#include "../Input/InputComponent.hpp"
#include <algorithm>

Camera::Camera(World* world) :
    GameObject(world),
    inputVelocity{},
    zoom(0.5),
    minZoom(0.2f),
    maxZoom(1)
{
    auto* inputComponent = createComponent<InputComponent>();
    inputComponent->registerEvent(
        InputEvent::Camera_X,
        [this](float value) { inputVelocity.x = value; }
    );
    inputComponent->registerEvent(
        InputEvent::Camera_Y,
        [this](float value) { inputVelocity.y = value; }
    );
    inputComponent->registerEvent(
        InputEvent::CameraZoom,
        [this](float value) { zoom = std::clamp(zoom + value * 0.05f, minZoom, maxZoom); }
    );
}

void Camera::tick(uint32_t deltaTime)
{
    position.x += inputVelocity.x * deltaTime;
    position.y += inputVelocity.y * deltaTime; 
}

#include "Camera.hpp"
#include "../Input/InputComponent.hpp"
#include <algorithm>

Camera::Camera(const Engine* engine) :
    GameObject(engine),
    inputVelocity{},
    zoom(1)
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
        [this](float value) { zoom = std::clamp(zoom + value * 0.25f, 0.5f, 4.0f); }
    );
}

void Camera::tick(uint32_t deltaTime)
{
    position.x += inputVelocity.x * deltaTime;
    position.y += inputVelocity.y * deltaTime; 
}

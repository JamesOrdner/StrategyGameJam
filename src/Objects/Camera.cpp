#include "Camera.hpp"
#include "../Input/InputComponent.hpp"

Camera::Camera(const Engine* engine) :
    GameObject(engine),
    inputVelocity{}
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
}

void Camera::tick(uint32_t deltaTime)
{
    position.x += inputVelocity.x * deltaTime;    
}

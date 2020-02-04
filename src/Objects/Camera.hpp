#ifndef Camera_hpp
#define Camera_hpp

#include "../Engine/GameObject.hpp"
#include <SDL_rect.h>

class Camera : public GameObject
{
public:
    
    Camera(const class Engine* engine);
    
    void tick(uint32_t deltaTime) override;
    
private:
    
    /// Input velocity of the camera with range [-1, 1]
    SDL_FPoint inputVelocity;
};

#endif /* Camera_hpp */

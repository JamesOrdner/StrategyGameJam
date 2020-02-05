#ifndef GraphicsComponent_hpp
#define GraphicsComponent_hpp

#include "../Engine/GameObjectComponent.hpp"
#include <SDL_pixels.h>
#include <memory>

class GraphicsComponent : public GameObjectComponent
{
public:
    
    GraphicsComponent(class GameObject* owner);
    
    ~GraphicsComponent();
    
    void setRenderer(const class Renderer* renderer);
    
    void setSprite(int width, int height, SDL_Color color);
    
    void draw();
    
private:
    
    const class Renderer* renderer;
    
    std::unique_ptr<struct Sprite> sprite;
};

#endif /* GraphicsComponent_hpp */

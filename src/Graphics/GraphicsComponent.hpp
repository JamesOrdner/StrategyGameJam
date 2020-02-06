#ifndef GraphicsComponent_hpp
#define GraphicsComponent_hpp

#include "../Engine/GameObjectComponent.hpp"
#include <SDL_pixels.h>
#include <memory>

enum class RenderDepth
{
    Terrain
};

class GraphicsComponent : public GameObjectComponent
{
public:
    
    GraphicsComponent(class GameObject* owner);
    
    ~GraphicsComponent();
    
    void setRenderer(const class Renderer* renderer);
    
    void setSprite(int width, int height, const SDL_Color& color);
    
    void draw();
    
    RenderDepth renderDepth;
    
private:
    
    friend class Graphics;
    
    /// TODO: Remove after implementing texture-only sprites
    const class Renderer* renderer;
    
    std::unique_ptr<struct Sprite> sprite;
    
    /// Graphics checks for dirty RenderDepth if this differs from renderDepth
    RenderDepth oldRenderDepth;
};

#endif /* GraphicsComponent_hpp */

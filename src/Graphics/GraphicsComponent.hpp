#ifndef GraphicsComponent_hpp
#define GraphicsComponent_hpp

#include "../Engine/GameObjectComponent.hpp"
#include <SDL_pixels.h>
#include <string>
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
    
    void setSprite(int width, int height, const SDL_Color& color);
    
    void setSprite(const std::string& filepath);
    
    void draw();
    
    RenderDepth renderDepth;
    
private:
    
    friend class Graphics;
    
    class Renderer* renderer;
    
    std::unique_ptr<struct Sprite> sprite;
    
    /// Graphics checks for dirty RenderDepth if this differs from renderDepth
    RenderDepth oldRenderDepth;
};

#endif /* GraphicsComponent_hpp */

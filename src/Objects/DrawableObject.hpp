#ifndef DrawableObject_hpp
#define DrawableObject_hpp

#include "../Engine/GameObject.hpp"
#include "../Graphics/GraphicsComponent.hpp"

class DrawableObject : public GameObject
{
public:
    
    DrawableObject(const class Engine* engine);
    
    void setSprite(int width, int height, const struct SDL_Color& color);
    
    void setRenderDepth(RenderDepth depth);

private:
    GraphicsComponent* graphicsComponent;
};

#endif /* DrawableObject_hpp */

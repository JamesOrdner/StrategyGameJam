#ifndef DrawableObject_hpp
#define DrawableObject_hpp

#include "../Engine/GameObject.hpp"

class DrawableObject : public GameObject
{
public:
    
    DrawableObject(const class Engine* engine);
    
    void setSprite(int width, int height, const struct SDL_Color& color);

private:
    class GraphicsComponent* graphicsComponent;
};

#endif /* DrawableObject_hpp */

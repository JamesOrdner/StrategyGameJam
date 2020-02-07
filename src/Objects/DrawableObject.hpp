#ifndef DrawableObject_hpp
#define DrawableObject_hpp

#include "../Engine/GameObject.hpp"
#include "../Graphics/GraphicsComponent.hpp"
#include "../Physics/PhysicsComponent.hpp"

class DrawableObject : public GameObject
{
public:
    
    DrawableObject(class World* world, const SDL_FPoint& position);
    
    void setSprite(int width, int height, const struct SDL_Color& color);
    
    void setSprite(const std::string& filepath);
    
    void setRenderDepth(RenderDepth depth);
    
    void setPhysics(PhysicsType type);

private:
    
    class GraphicsComponent* graphicsComponent;
    
    class PhysicsComponent* physicsComponent;
};

#endif /* DrawableObject_hpp */

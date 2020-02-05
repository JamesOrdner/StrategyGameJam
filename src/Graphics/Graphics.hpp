#ifndef Graphics_hpp
#define Graphics_hpp

#include "../Engine/GameSystem.hpp"
#include <SDL_rect.h>
#include <memory>
#include <vector>

class Graphics : public GameSystem
{
public:
    
    Graphics(const class Engine* engine);
    
    ~Graphics();
    
    void init() override;
    void deinit() override;
    bool execute(uint32_t deltaTime) override;
    void registerComponent(class GameObjectComponent* component) override;
    void unregisterComponent(class GameObjectComponent* component) override;
    
    void setCamera(const class Camera* cameraObject);
    
    SDL_Point screenToWorldCoords(const SDL_Point& point) const;
    
private:
    
    /// All registered graphics components
    std::vector<class GraphicsComponent*> graphicsComponents;
    
    std::unique_ptr<class Renderer> renderer;
    
    const class Camera* camera;
};

#endif /* Graphics_hpp */

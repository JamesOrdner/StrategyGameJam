#ifndef Graphics_hpp
#define Graphics_hpp

#include "../Engine/GameSystem.hpp"
#include <memory>
#include <vector>

class Graphics : public GameSystem
{
public:
    
    Graphics();
    
    ~Graphics();
    
    void init() override;
    void deinit() override;
    bool execute(uint32_t deltaTime) override;
    void registerComponent(class GameObjectComponent* component) override;
    void unregisterComponent(class GameObjectComponent* component) override;
    
    void setCamera(const class GameObject* cameraObject);
    
private:
    
    /// All registered graphics components
    std::vector<class GraphicsComponent*> graphicsComponents;
    
    std::unique_ptr<class Renderer> renderer;
    
    const class GameObject* camera;
};

#endif /* Graphics_hpp */

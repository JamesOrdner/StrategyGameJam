#ifndef Graphics_hpp
#define Graphics_hpp

#include "../Engine/GameSystem.hpp"
#include <memory>

class Graphics : public GameSystem
{
public:
    
    Graphics();
    
    ~Graphics();
    
    void init() override;
    void deinit() override;
    bool execute(uint32_t deltaTime) override;
    void registerComponent(class GObjectComponent* component) override;
    void unregisterComponent(class GObjectComponent* component) override;
    
private:
    
    std::unique_ptr<class Renderer> renderer;
};

#endif /* Graphics_hpp */

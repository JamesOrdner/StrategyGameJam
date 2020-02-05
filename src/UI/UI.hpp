#ifndef UI_hpp
#define UI_hpp

#include "../Engine/GameSystem.hpp"
#include <vector>

class UI : public GameSystem
{
public:
    
    UI(const class Engine* engine);
    
    bool execute(uint32_t deltaTime) override;
    void registerComponent(class GameObjectComponent* component) override;
    void unregisterComponent(class GameObjectComponent* component) override;
    
private:
    
    /// All registered AI components
    std::vector<class UIComponent*> uiComponents;
};

#endif /* UI_hpp */

#ifndef UI_hpp
#define UI_hpp

#include "../Engine/GameSystem.hpp"
#include <vector>
#include <memory>

class UI : public GameSystem
{
public:
    
    UI(const class Engine* engine);
    
    ~UI();
    
    bool execute(uint32_t deltaTime) override;
    void registerComponent(class GameObjectComponent* component) override;
    void unregisterComponent(class GameObjectComponent* component) override;
    
    struct UIObject* rootUIObjectPtr() const { return rootUIObject.get(); }
    
private:
    
    /// All registered AI components
    std::vector<class UIComponent*> uiComponents;
    
    std::unique_ptr<struct UIObject> rootUIObject;
};

#endif /* UI_hpp */

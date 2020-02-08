#include "UI.hpp"
#include "UIComponent.hpp"
#include "UIObject.hpp"
#include "../Engine/GameState.hpp"
#include "../Engine/GameObject.hpp"
#include <algorithm>

UI::UI(const Engine* engine) :
    GameSystem(engine)
{
    rootUIObject = std::make_unique<UIObject>();
}

UI::~UI()
{
}

void UI::init()
{
    auto& money = rootUIObject->subobjects.emplace_back();
    money.anchor = UIAnchor::TopRight;
    money.bounds = { -15, 0, 0, 0 };
    money.text = "0";
}

void UI::deinit()
{
    rootUIObject->subobjects.clear();
}

bool UI::execute(uint32_t deltaTime)
{
    // update on screen selection
    for (auto& selectHUD : rootUIObject->subobjects) {
        if (selectHUD.uiComponent) {
            selectHUD.bHidden = !selectHUD.uiComponent->bSelected;
            selectHUD.bounds.x = selectHUD.uiComponent->owner->position.x;
            selectHUD.bounds.y = selectHUD.uiComponent->owner->position.y;
        }
    }
    
    // update money
    rootUIObject->subobjects[0].text = std::to_string(engine->gameStatePtr()->getMoney());
    
    return true;
}

void UI::registerComponent(class GameObjectComponent* component)
{
    if (auto* uiComponent = dynamic_cast<UIComponent*>(component)) {
        uiComponents.emplace_back(uiComponent);
        
        auto& selectImage = rootUIObject->subobjects.emplace_back();
        selectImage.anchor = UIAnchor::World;
        selectImage.bounds = { 0, 0, 300, 300 };
        selectImage.textureFilepath = "res/textures/ui/selected_circle.bmp";
        selectImage.uiComponent = uiComponent;
    }
}

void UI::unregisterComponent(class GameObjectComponent* component)
{
    if (auto* uiComponent = dynamic_cast<UIComponent*>(component)) {
        uiComponents.erase(std::remove(uiComponents.begin(), uiComponents.end(), uiComponent));
        
        auto& rootObjects = rootUIObject->subobjects;
        for (auto it = rootObjects.begin(); it != rootObjects.end(); it++) {
            if (it->uiComponent == uiComponent) {
                rootObjects.erase(it);
                break;
            }
        }
    }
}

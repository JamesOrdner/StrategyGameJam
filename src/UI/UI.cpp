#include "UI.hpp"
#include "UIComponent.hpp"
#include "UIObject.hpp"
#include "../Engine/GameState.hpp"
#include "../Engine/GameObject.hpp"
#include <algorithm>

constexpr int virtualWidth = 1280;
constexpr int virtualHeight = 720;

UI::UI(const Engine* engine) :
    GameSystem(engine)
{
    rootUIObject = std::make_unique<UIObject>();
    rootUIObject->subobjects.emplace_back().bounds = { virtualWidth, virtualHeight }; // UI-reserved
    rootUIObject->subobjects.emplace_back().bounds = { virtualWidth, virtualHeight }; // UIComponents
    
    auto& money = rootUIObject->subobjects[0].subobjects.emplace_back();
    money.anchor = UIAnchor::TopRight;
    money.bounds = { -15, 0, 0, 0 };
    money.text = "0";
    
    auto& spawnUnit1 = rootUIObject->subobjects[0].subobjects.emplace_back();
    spawnUnit1.anchor = UIAnchor::Bottom;
    spawnUnit1.bounds = { 0, 0, 160, 160 };
    spawnUnit1.textureFilepath = "res/textures/ui/item_box.bmp";
    spawnUnit1.bAcceptsInput = true;
    spawnUnit1.callback = []{ printf("button\n"); };
}

UI::~UI()
{
}

void UI::init()
{
}

void UI::deinit()
{
    rootUIObject->subobjects[1].subobjects.clear();
}

bool UI::execute(uint32_t deltaTime)
{
    // update UIComponent UIObjects
    for (auto& selectHUD : rootUIObject->subobjects[1].subobjects) {
        if (selectHUD.uiComponent) {
            selectHUD.bHidden = !selectHUD.uiComponent->bSelected;
            selectHUD.bounds.x = selectHUD.uiComponent->owner->position.x;
            selectHUD.bounds.y = selectHUD.uiComponent->owner->position.y;
        }
    }
    
    // update money
    rootUIObject->subobjects[0].subobjects[0].text = std::to_string(engine->gameStatePtr()->getMoney());
    
    return true;
}

void UI::registerComponent(class GameObjectComponent* component)
{
    if (auto* uiComponent = dynamic_cast<UIComponent*>(component)) {
        uiComponents.emplace_back(uiComponent);
        
        auto& selectImage = rootUIObject->subobjects[1].subobjects.emplace_back();
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
        
        auto& uiCompObjects = rootUIObject->subobjects[1].subobjects;
        for (auto it = uiCompObjects.begin(); it != uiCompObjects.end(); it++) {
            if (it->uiComponent == uiComponent) {
                uiCompObjects.erase(it);
                break;
            }
        }
    }
}

bool UI::processInput(const SDL_Event& event, const UIObject* object)
{
    if (!object || event.type != SDL_MOUSEBUTTONDOWN) return false;
    if (object->callback) object->callback();
    return event.type == SDL_MOUSEBUTTONDOWN;
}

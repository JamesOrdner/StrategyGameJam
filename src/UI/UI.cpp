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
    rootUIObject->subobjects.emplace_back(); // UI-reserved
    rootUIObject->subobjects.emplace_back(); // UIComponents
    
    auto& money = rootUIObject->subobjects[0].subobjects.emplace_back();
    money.name = "money";
    money.anchor = UIAnchor::TopRight;
    money.bounds = { -15, 0, 0, 0 };
    money.text = "0";
    money.textSize = TextSize::Large;
    
    auto& wood = rootUIObject->subobjects[0].subobjects.emplace_back();
    wood.name = "wood";
    wood.anchor = UIAnchor::TopLeft;
    wood.bounds = { 15, 0, 0, 0 };
    wood.text = "Wood: 0";
    
    auto& iron = rootUIObject->subobjects[0].subobjects.emplace_back();
    iron.name = "iron";
    iron.anchor = UIAnchor::TopLeft;
    iron.bounds = { 15, 35, 0, 0 };
    iron.text = "Iron: 0";
    
    auto& crystal = rootUIObject->subobjects[0].subobjects.emplace_back();
    crystal.name = "crystal";
    crystal.anchor = UIAnchor::TopLeft;
    crystal.bounds = { 15, 70, 0, 0 };
    crystal.text = "Crysal: 0";
    
    auto& wolf = rootUIObject->subobjects[0].subobjects.emplace_back();
    wolf.name = "wolf";
    wolf.anchor = UIAnchor::TopLeft;
    wolf.bounds = { 15, 105, 0, 0 };
    wolf.text = "Wolf: 0";
    
    auto& spawnUnit1 = rootUIObject->subobjects[0].subobjects.emplace_back();
    spawnUnit1.anchor = UIAnchor::Bottom;
    spawnUnit1.bounds = { 0, 0, 160, 160 };
    spawnUnit1.textureFilepath = "res/textures/ui/item_box_red.bmp";
    spawnUnit1.bAcceptsInput = true;
    spawnUnit1.unitSpawnType = PlayerUnit::Clubman;
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
    
    auto* gameState = engine->gameStatePtr();
    for (auto& object : rootUIObject->subobjects[0].subobjects) {
        // update buildables
        if (object.unitSpawnType.has_value()) {
            if (gameState->isUnitBuildable(object.unitSpawnType.value())) {
                object.textureFilepath = "res/textures/ui/item_box.bmp";
            }
            else {
                object.textureFilepath = "res/textures/ui/item_box_red.bmp";
            }
        }
        else if (object.name == "money") {
            object.text = std::to_string(gameState->getMoney());
        }
        else if (object.name == "wood") {
            object.text = "Wood: " + std::to_string(gameState->getResourceCount(ResourceType::Wood));
        }
        else if (object.name == "iron") {
            object.text = "Iron: " + std::to_string(gameState->getResourceCount(ResourceType::Iron));
        }
        else if (object.name == "crystal") {
            object.text = "Crystal: " + std::to_string(gameState->getResourceCount(ResourceType::Crystal));
        }
        else if (object.name == "wolf") {
            object.text = "Wolf: " + std::to_string(gameState->getResourceCount(ResourceType::Wolf));
        }
    }
    
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
    if (object->unitSpawnType.has_value()) {
        engine->gameStatePtr()->buildUnit(object->unitSpawnType.value());
    }
    return event.type == SDL_MOUSEBUTTONDOWN;
}

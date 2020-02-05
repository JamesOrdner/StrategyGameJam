#include "UI.hpp"
#include "UIComponent.hpp"
#include "UIObject.hpp"
#include <algorithm>

UI::UI(const Engine* engine) :
    GameSystem(engine)
{
    rootUIObject = std::make_unique<UIObject>();
}

UI::~UI()
{
}

bool UI::execute(uint32_t deltaTime)
{
    return true;
}

void UI::registerComponent(class GameObjectComponent* component)
{
    if (auto* uiComponent = dynamic_cast<UIComponent*>(component)) {
        uiComponents.emplace_back(uiComponent);
    }
}

void UI::unregisterComponent(class GameObjectComponent* component)
{
    auto* uiComponent = dynamic_cast<UIComponent*>(component);
    auto it = std::remove(uiComponents.begin(), uiComponents.end(), uiComponent);
    if (it != uiComponents.end()) uiComponents.erase(it);
}

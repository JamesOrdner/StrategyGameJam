#ifndef UIObject_hpp
#define UIObject_hpp

#include <SDL_rect.h>
#include <string>
#include <vector>

enum class UIAnchor
{
    Center,
    Top,
    Bottom,
    Left,
    Right,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    World // coordinates in world space
};

struct UIObject
{
    UIObject() :
        bounds{},
        rotation(0),
        anchor(UIAnchor::Center),
        bHidden(false),
        uiComponent(nullptr)
    {
    }
    
    /// Bounds of the UIObject, includes position
    SDL_Rect bounds;
    
    /// Rendered text
    std::string text;
    
    /// Coordinates for this UIObject on the UI texture sheet
    std::string textureFilepath;
    
    /// Rotation in degrees
    double rotation;
    
    /// Anchor affects both the anchor position relative to the parent layer, as well
    /// as the edge/corner of this UIObject that the position is defined relative to
    UIAnchor anchor;
    
    /// Should this UIObject render? Also affects all subobjects
    bool bHidden;
    
    std::vector<UIObject> subobjects;
    
private:
    
    friend class UI;
    
    class UIComponent* uiComponent;
};

#endif /* UIObject_hpp */

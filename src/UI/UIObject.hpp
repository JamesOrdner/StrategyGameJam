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
    BottomRight
};

struct UIObject
{
    /// Bounds of the UIObject, includes position
    SDL_Rect bounds;
    
    /// Coordinates for this UIObject on the UI texture sheet
    std::string textureFilepath;
    
    /// Rotation in degrees
    double rotation;
    
    /// Anchor affects both the anchor position relative to the parent layer, as well
    /// as the edge/corner of this UIObject that the position is defined relative to
    UIAnchor anchor;
    
    std::vector<UIObject> subobjects;
    
    UIObject() : bounds{}, rotation(0), anchor(UIAnchor::Center) {}
};

#endif /* UIObject_hpp */

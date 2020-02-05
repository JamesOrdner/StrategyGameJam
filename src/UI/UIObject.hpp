#ifndef UIObject_hpp
#define UIObject_hpp

#include <SDL_rect.h>

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
    SDL_Rect textureCoords;
    
    /// Anchor affects both the anchor position relative to the parent layer, as well
    /// as the edge/corner of this UIObject that the position is defined relative to
    UIAnchor anchor;
};

#endif /* UIObject_hpp */

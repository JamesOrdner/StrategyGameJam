#ifndef Sprite_hpp
#define Sprite_hpp

#include <SDL_render.h>
#include <string>

struct Sprite
{
public:
    
    /// Create a simple rectangular, solid-colored sprite
    Sprite(SDL_Renderer* renderer, const SDL_Rect& size, Uint32 color);
    
    /// Provide a filepath to load a sprite from file
    Sprite(const std::string& filepath);
    
    ~Sprite();
    
    /// The solid color texture used by this sprite, or nullptr if sprite loaded from file
    SDL_Texture* texture;
    
    /// The filepath of the sprite if loaded from file, or empty string if a custom texture was created
    std::string filepath;
    
    /// Stores the length and width of the texture. The position component of SDL_Rect is
    /// the offset required so that the sprite is drawn relative to the center of the texture
    SDL_Rect bounds;
};

#endif /* Sprite_hpp */

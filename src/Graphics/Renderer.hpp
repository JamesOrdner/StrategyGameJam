#ifndef Renderer_hpp
#define Renderer_hpp

#include "../UI/UIObject.hpp"
#include <SDL_ttf.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <map>
#include <string>

class Renderer
{
public:
    
    Renderer();
    
    ~Renderer();
    
    void clear() const;
    
    /// Draw a texture to the specified screen destination
    void draw(SDL_Texture* texture, SDL_Rect dest, double rotation) const;
    
    /// Draw a named texture to a world position
    void draw(const std::string& filepath, const SDL_Point& position, double rotation);
    
    /// Draws the UI
    void drawUI(const UIObject* rootObject);
    
    void present() const;
    
    inline SDL_Renderer* sdlRenderer() const { return renderer; }
    
    SDL_Point screenToWorldCoords(const SDL_Point& point) const;
    
    /// Zoom multiplier for high dpi displays
    float hidpiMult;
    
    /// Defaults to 1.f, depends on the game camera
    float zoom;
    
    /// Amount to offset all drawn object, dependent on camera
    SDL_Point cameraOffset;
    
private:
    
    SDL_Window* window;
    
    SDL_Renderer* renderer;
    
    TTF_Font* font;
    
    struct TextureAsset
    {
        SDL_Texture* texture;
        SDL_Rect bounds;
    };
    
    /// Maps texture filepaths to their loaded texture, which will be created upon first access.
    /// This should only be accessed via the texture() function!
    std::map<std::string, TextureAsset> textureAssets;
    
    void drawSurface(SDL_Surface* surface, const SDL_Point& point, UIAnchor anchor);
    
    /// Return the SDL_Texture pointer for the given texture filepath
    const TextureAsset& texture(const std::string& filepath);
    
    /// Caller is responsible for freeing texture
    SDL_Surface* genTextTexture(const std::string& text, SDL_Color color);
    
    /// Actual HiDPI pixel resolution
    int screenWidth, screenHeight;
    
    /// Non-HiDPI window resolution
    int windowWidth, windowHeight;
    
    /// Draws the UI recursively
    void drawUI(const struct UIObject& object, const SDL_Rect& parentBoundsAbs);
};

#endif /* Renderer_hpp */

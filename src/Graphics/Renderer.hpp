#ifndef Renderer_hpp
#define Renderer_hpp

#include <SDL_video.h>
#include <SDL_render.h>

class Renderer
{
public:
    
    Renderer();
    
    ~Renderer();
    
    void clear() const;
    
    /// Draws the world
    void draw(SDL_Texture* texture, SDL_Rect dest, double rotation) const;
    
    /// Draws the UI
    void drawUI(const struct UIObject* rootObject);
    
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
    
    /// Actual HiDPI pixel resolution
    int screenWidth, screenHeight;
    
    /// Non-HiDPI window resolution
    int windowWidth, windowHeight;
    
    /// Draws the UI recursively
    void drawUI(const struct UIObject& object, const SDL_Rect& parentBoundsAbs);
};

#endif /* Renderer_hpp */

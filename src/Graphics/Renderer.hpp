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
    
    void draw(SDL_Texture* texture, SDL_Rect dest, double rotation) const;
    
    void present() const;
    
    inline SDL_Renderer* sdlRenderer() const { return renderer; }
    
    /// Zoom multiplier for high dpi displays
    float hidpiMult;
    
    /// Defaults to 1.f, depends on the game camera
    float zoom;
    
    /// Amount to offset all drawn object, dependent on camera
    SDL_Point cameraOffset;
    
private:
    
    SDL_Window* window;
    
    SDL_Renderer* renderer;
    
    int screenWidth, screenHeight;
};

#endif /* Renderer_hpp */

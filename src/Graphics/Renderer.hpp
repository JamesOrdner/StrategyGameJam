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
    
    /// Defaults to 1.f, depends on the game camera
    float zoom;
    
private:
    
    SDL_Window* window;
    
    SDL_Renderer* renderer;
    
    int screenWidth, screenHeight;
};

#endif /* Renderer_hpp */

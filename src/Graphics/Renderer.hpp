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
    
    void draw(SDL_Texture* texture, const SDL_Rect& dest, double rotation) const;
    
    void present() const;
    
    inline SDL_Renderer* sdlRenderer() const { return renderer; }
    
private:
    
    SDL_Window* window;
    
    SDL_Renderer* renderer;
};

#endif /* Renderer_hpp */

#ifndef Renderer_hpp
#define Renderer_hpp

#include <SDL_video.h>
#include <SDL_render.h>

class Renderer
{
public:
    
    Renderer();
    
    ~Renderer();
    
    void draw();
    
private:
    
    SDL_Window* window;
    
    SDL_Renderer* renderer;
};

#endif /* Renderer_hpp */

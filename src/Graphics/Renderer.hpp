#ifndef Renderer_hpp
#define Renderer_hpp

#include "../Engine/GameSystem.hpp"
#include <SDL_video.h>
#include <SDL_render.h>

class Renderer : public GameSystem
{
public:
    
    Renderer();
    
    ~Renderer();
    
    void init() override;
    void deinit() override;
    bool execute(uint32_t deltaTime) override;
    
private:
    
    SDL_Window* window;
    
    SDL_Renderer* renderer;
};

#endif /* Renderer_hpp */

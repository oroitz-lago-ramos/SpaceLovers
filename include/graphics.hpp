#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <SDL2/SDL.h>

class Graphics
{
public:
    Graphics();
    ~Graphics();
    static SDL_Window *window;
    static SDL_Renderer *renderer;
    
};


#endif
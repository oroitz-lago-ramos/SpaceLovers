#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <SDL2/SDL.h>
#include <set>

#include "button.hpp"
#include "enemy.hpp"

class Graphics
{
public:
    Graphics();
    ~Graphics();
    static SDL_Window *window;
    static SDL_Renderer *renderer;

    static int screenWidth;
    static int screenHeight;
    static int windowWidth;
    
    //Include de "set" afin de créer un tableau de tous les (Button *) le tableau s'appelle buttons
    static std::set<Button *> buttons;
};


#endif
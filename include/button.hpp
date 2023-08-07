#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "functional"
#include <SDL2/SDL.h>

class Button
{
public:
    Button();
    Button(int r, int g, int b, SDL_Rect rect, std::function<void()> onClick);
    ~Button();
    void render();

    int r;
    int g;
    int b;
    SDL_Rect rect;
    std::function<void()> onClick;
};

#endif
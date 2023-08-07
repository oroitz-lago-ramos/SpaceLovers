#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "functional"
#include <SDL2/SDL.h>
#include "entity.hpp"

class Button:public Entity
{
public:
    Button(int r, int g, int b, SDL_Rect rect, std::function<void()> onClick);
    ~Button();

    std::function<void()> onClick;
};

#endif
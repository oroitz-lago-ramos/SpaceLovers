#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "functional"
#include <SDL2/SDL.h>
#include "entity.hpp"

class Button:public Entity
{
public:
    Button(int r, int g, int b,  int x, int y, int width, int height, std::function<void()> onClick, char* message);
    ~Button();

    char* message;

    std::function<void()> onClick;
    void text();
};

#endif
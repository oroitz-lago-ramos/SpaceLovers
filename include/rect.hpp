#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

class Rect:public Entity
{
public:
    Rect();
    Rect(int r, int g, int b, int x, int y, int width, int height);
    RectFill(int r, int g, int b, int x, int y, int width, int height);
    ~Rect();
}
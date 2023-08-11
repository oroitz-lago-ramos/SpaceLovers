#ifndef RECT_HPP
#define RECT_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

class Rect : public Entity
{
public:
    Rect(int r, int g, int b, int x, int y, int width, int height);
    ~Rect();
    void render(bool fill);
};

#endif
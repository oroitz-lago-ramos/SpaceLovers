#ifndef INGAMEITEM_HPP
#define INGAMEITEM_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

class InGameItem : public Entity
{
public:
    InGameItem(int r, int g, int b, SDL_Rect rect);
    ~InGameItem();
};

#endif
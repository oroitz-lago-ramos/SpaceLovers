#include <iostream>
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "inGameItem.hpp"

InGameItem::InGameItem(int r, int g, int b, SDL_Rect rect)
    : Entity(r, g, b, rect)
{
}

InGameItem::~InGameItem()
{
}
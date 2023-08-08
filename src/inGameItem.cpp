#include <iostream>
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "inGameItem.hpp"

InGameItem::InGameItem(int r, int g, int b, int x, int y, int width, int height)
    : Entity(r, g, b, x, y, width, height)
{
}

InGameItem::~InGameItem()
{
}
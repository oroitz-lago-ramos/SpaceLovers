#include <iostream>
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "character.hpp"

Character::Character(int r, int g, int b, SDL_Rect rect, float speed)
    : Entity(r, g, b, rect),
    speed(speed),
    x(rect.x),
    y(rect.y)
{
}

Character::~Character()
{
}

void Character::moveUp()
{
    y -= speed;
    rect.y = (int)y;
}

void Character::moveDown()
{
    y += speed;
    rect.y = (int)y;
}

void Character::moveRight()
{
    x += speed;
    rect.x = (int)x;
}

void Character::moveLeft()
{
    x -= speed;
    rect.x = (int)x;
}



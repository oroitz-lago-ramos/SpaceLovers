#include <iostream>
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "character.hpp"

Character::Character(int r, int g, int b, SDL_Rect rect, float speed)
    : Entity(r, g, b, rect),
    speed(speed)
{
}

Character::~Character()
{
}

void Character::moveUp()
{
}

void Character::moveDown()
{
}

void Character::moveRight()
{
}

void Character::moveLeft()
{
}



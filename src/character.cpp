#include <iostream>
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "character.hpp"

Character::Character(int r, int g, int b, SDL_Rect rect)
    : Entity(r, g, b, rect)
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

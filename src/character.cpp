#include <iostream>
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "character.hpp"
#include "game.hpp"

Character::Character(int r, int g, int b, int x, int y, int width, int height, float speed)
    : Entity(r, g, b, x, y, width, height),
    speed(speed), lifePoints(lifePoints)
{
}

Character::~Character()
{
}

void Character::moveUp()
{
    this -> setY(this -> getY() - this ->speed * Game::frameTime / 100000);  
}

void Character::moveDown()
{
    this -> setY(this -> getY() + this ->speed * Game::frameTime / 100000);
}

void Character::moveRight()
{
    this -> setX(this -> getX() + this ->speed * Game::frameTime / 100000);  
}

void Character::moveLeft()
{
    this -> setX(this -> getX() - this ->speed * Game::frameTime / 100000);  
    
}

void Character::takeDamage(float damage)
{
	this->lifePoints -= damage;
}


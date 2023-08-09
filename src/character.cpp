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
    this -> setY(this -> getY() - this ->speed);  
}

void Character::moveDown()
{
    this -> setY(this -> getY() + this ->speed);
}

void Character::moveRight()
{
    this -> setX(this -> getX() + this ->speed);  
}

void Character::moveLeft()
{
    this -> setX(this -> getX() - this ->speed);  
    
}

void Character::takeDamage(float damage)
{
	if (this->lifePoints > damage)
	{
		this->lifePoints -= damage;
	}
	else
	{
		Game::isRunning = false;
	}
}


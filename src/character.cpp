#include <iostream>
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "character.hpp"
#include "game.hpp"
#include "level.hpp"

Character::Character(int r, int g, int b, int x, int y, int width, int height, float speed, float lifePoints, float power, float defense)
	: Entity(r, g, b, x, y, width, height),
	  speed(speed), lifePoints(lifePoints), maxLifePoints(lifePoints), power(power), defense(defense)
{
}

Character::Character(int r, int g, int b, int x, int y, int width, int height, float speed, float lifePoints)
	: Entity(r, g, b, x, y, width, height),
	  speed(speed), lifePoints(lifePoints), maxLifePoints(lifePoints)
{
}

Character::Character(int r, int g, int b, int x, int y, int width, int height, float speed)
	: Entity(r, g, b, x, y, width, height),
	  speed(speed), lifePoints(1), maxLifePoints(1)
{
}

Character::~Character()
{
}

void Character::moveUp()
{
	this->setY(this->getY() - this->speed * Game::frameTime / 100000);
}

void Character::moveDown()
{
	this->setY(this->getY() + this->speed * Game::frameTime / 100000);
}

void Character::moveRight()
{
	this->setX(this->getX() + this->speed * Game::frameTime / 100000);
}

void Character::moveLeft()
{
	this->setX(this->getX() - this->speed * Game::frameTime / 100000);
}

void Character::takeDamage(float damage)
{
	this->lifePoints -= damage;
}

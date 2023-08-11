#include <iostream>
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "character.hpp"
#include "game.hpp"
#include "level.hpp"

Character::Character(int r, int g, int b, int x, int y, int width, int height, float speed, float lifePoints, int power, float defense)
    : Entity(r, g, b, x, y, width, height),
      speed(speed), lifePoints(lifePoints), maxLifePoints(lifePoints), power(power), defense(defense)
{
}

Character::Character(int r, int g, int b, int x, int y, int width, int height, float speed, float dirX, float dirY)
	: Entity(r, g, b, x, y, width, height),
	speed(speed), lifePoints(1), maxLifePoints(1), dirX(dirX), dirY(dirY)
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

void Character::move()
{
	this->setX(this->getX() + this->dirX * this->speed * Game::frameTime / 100000);
	this->setY(this->getY() + this->dirY * this->speed * Game::frameTime / 100000);
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

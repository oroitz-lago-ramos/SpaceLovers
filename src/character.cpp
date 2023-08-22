#include <iostream>
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "character.hpp"
#include "game.hpp"
#include "level.hpp"

Character::Character(int r, int g, int b, int x, int y, int width, int height, float speed, float lifePoints, float power, float defense)
	: Entity(r, g, b, x, y, width, height),
	  speed(speed), lifePoints(lifePoints), maxLifePoints(lifePoints), power(power), defense(defense), asTakeDamage(0), isPlayer(false)
{
}

Character::Character(int r, int g, int b, int x, int y, int width, int height, float speed, float lifePoints, float power, float defense, float shield)
	: Entity(r, g, b, x, y, width, height),
	  speed(speed), lifePoints(lifePoints), maxLifePoints(lifePoints), power(power), defense(defense), shield(shield), maxShield(shield), asTakeDamage(0), isPlayer(false)
{
}

Character::Character(int r, int g, int b, int x, int y, int width, int height, float speed, float dirX, float dirY)
	: Entity(r, g, b, x, y, width, height),
	  speed(speed), lifePoints(1), maxLifePoints(1), dirX(dirX), dirY(dirY), asTakeDamage(0), isPlayer(false)
{
}

Character::Character(int r, int g, int b, int x, int y, int width, int height, float speed)
	: Entity(r, g, b, x, y, width, height),
	  speed(speed), lifePoints(1), maxLifePoints(1), asTakeDamage(0), isPlayer(false)
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
	if (this->isPlayer && this->asTakeDamage < 150000000)
	{
		return;
	}
	if (this->shield > 0)
	{
		this->shield -= damage;
		if (damage > this->shield)
		{
			damage = damage - this->shield;
			this->lifePoints -= damage * (100-this->defense) / 100;
		}
	}
	this->lifePoints -= damage * (100-this->defense) / 100;
	this->asTakeDamage = 0;
}

void Character::renderShield()
{
	if (this->maxShield == 0)
	{
		return;
	}
	if (this->shield > 0)
	{
		this->shieldColor = this->shield / this->maxShield * 100;
		SDL_SetRenderDrawColor(Graphics::renderer, this->shieldColor, this->shieldColor, this->shieldColor, 100);
		SDL_RenderFillCircle(this->getX(), this->getY(), this->getWidth() / 1.7);
	}
}
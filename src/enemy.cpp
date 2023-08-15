#include <iostream>
#include "functional"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#include "enemy.hpp"
#include "level.hpp"
#include "character.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include <vector>

Enemy::Enemy(float lifePoints, float power, float defense, float xpValue)
	: Character(200, 100, 100, (rand() % (Graphics::screenWidth - 40) + 20), 10, 20, 20, 0.01, lifePoints, power, defense),
	  xpValue(xpValue), flags(0)
{
	this->shield = 0;
	this->maxShield = 0;
	SDL_Surface *enemy = IMG_Load("assets/ennemies.png");
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, enemy);
	Level::enemies.insert(this);
	this->timeSinceLastShot = 0;
}

Enemy::Enemy(float lifePoints, float power, float defense, float xpValue, float shield, int flags)
	: Character(255, 0, 0, Graphics::screenWidth / 2, 10, 50, 30, 0.01, lifePoints, power, defense, shield),
	  xpValue(xpValue), flags(flags)
{
	SDL_Surface *boss = IMG_Load("assets/boss.png");
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, boss);
	Level::enemies.insert(this);
	this->timeSinceLastShot = 0;
	if (flags & ATTACKLASER)
	{
		this->attacks.push_back(new Attack(this, 0));
	}
	if (flags & ATTACKSWEEP)
	{
		this->attacks.push_back(new Attack(this, 1));
	}
}

Enemy::~Enemy()
{
	Level::enemies.erase(this);
	for (Attack *attack : this->attacks)
	{
		attack->~Attack();
	}
}

void Enemy::update()
{
	this->checkCollisions();
	this->timeSinceLastShot += Game::frameTime;
	if (!(this->flags & ISBOSS) && this->timeSinceLastShot > 1500000000)
	{
		this->shoot();
	}

	if (this->lifePoints <= 0)
	{
		this->die();
	}
	if (this->flags & ISBOSS && this->getY() >= Graphics::screenHeight / 5)
	{
		static int rightOrLeft = rand() % 2;
		if (rightOrLeft == 1)
		{
			this->moveRight();
		}
		else
		{
			this->moveLeft();
		}
		if (this->getX() >= Graphics::screenWidth)
		{
			rightOrLeft = 0;
		}
		if (this->getX() <= 0)
		{
			rightOrLeft = 1;
		}
	}
	else
	{
		this->moveDown();
	}
	if (this->rect.y > Graphics::screenHeight)
	{
		this->~Enemy();
	}
	for (Attack *attack : this->attacks)
	{
		attack->update();
	}
}

void Enemy::die()
{
	this->~Enemy();
	Player::instance->gainExperience(this->xpValue);
}

void Enemy::shoot()
{
	new Projectile(255, 0, 0, this->getX(), this->getY() + this->getHeight(), 1, this->power, 0.02f);
	this->timeSinceLastShot = 0;
}

void Enemy::checkCollisions()
{
	if (SDL_HasIntersection(&this->rect, &Player::instance->rect))
	{
		this->~Enemy();
		Player::instance->lifePoints /= 2;
	}
}
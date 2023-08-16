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
	: Character(200, 100, 100, (rand() % (Graphics::screenWidth - 40) + 20), 10, 40, 40, 0.01, lifePoints, power, defense),
	  xpValue(xpValue), flags(0)
{
	this->destroyTexture = false;
	this->shield = 0;
	this->maxShield = 0;
	this->texture = Graphics::textures[ENEMYTEXTURE1];
	SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);

	Level::enemies.insert(this);
	this->timeSinceLastShot = 0;
}

Enemy::Enemy(float lifePoints, float power, float defense, float xpValue, float shield, int flags)
	: Character(255, 0, 0, Graphics::screenWidth / 2, 10, 70, 50, 0.01, lifePoints, power, defense, shield),
	  xpValue(xpValue), flags(flags)
{
	this->destroyTexture = false;
	this->texture = Graphics::textures[ENEMYTEXTURE2];
	SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);

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
	this->asTakeDamage += Game::frameTime;
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
		if (this->getX() >= Graphics::screenWidth - 35)
		{
			rightOrLeft = 0;
		}
		if (this->getX() <= 0 + 35)
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
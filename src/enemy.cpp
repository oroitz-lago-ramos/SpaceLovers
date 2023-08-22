#include <iostream>
#include "functional"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#include "enemy.hpp"
#include "level.hpp"
#include "character.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include <set>

Enemy::Enemy(float lifePoints, float power, float defense, float xpValue)
	: Character(200, 100, 100, (rand() % (Graphics::screenWidth - 40) + 20), 10, 40, 40, 0.01, lifePoints, power, defense),
	  xpValue(xpValue), flags(0), maxY(Graphics::screenHeight / 2), rightOrLeft(rand() % 2)
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
	  xpValue(xpValue), flags(flags), maxY(Graphics::screenHeight / 5)
{
	this->destroyTexture = false;
	this->texture = Graphics::textures[ENEMYTEXTURE2];
	SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);

	Level::enemies.insert(this);
	this->timeSinceLastShot = 0;
	if (flags & ATTACKLASER)
	{
		this->attacks.insert(new Attack(this, 0));
	}
	if (flags & ATTACKSWEEP)
	{
		this->attacks.insert(new Attack(this, 1));
	}
}

Enemy::~Enemy()
{
	Level::enemies.erase(this);
	for (Attack *attack : std::set<Attack *>(this->attacks))
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
	
	if (this->getY() >= this -> maxY)
	{
		if (this->rightOrLeft == 1)
		{
			this->moveRight();
		}
		else
		{
			this->moveLeft();
		}
		if (this->getX() >= Graphics::screenWidth - 35 || this->getX() <= 0 + 35)
		{
			this->rightOrLeft ^= 1;
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
	for (Attack *attack : std::set<Attack * >(this->attacks))
	{
		attack->update();
	}
	
	if (this->lifePoints <= 0)
	{
		this->die();
	}
}

void Enemy::die()
{
	Level::instance->enemyKilled++;
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
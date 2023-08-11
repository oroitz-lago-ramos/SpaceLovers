#include <iostream>
#include "functional"
#include <SDL2/SDL.h>

#include "enemy.hpp"
#include "level.hpp"
#include "character.hpp"
#include "graphics.hpp"
#include "game.hpp"

Enemy::Enemy(float power, float defense, float lifePoint, float xpValue)
	: Character(255, 0, 0, (rand() % (Graphics::screenWidth - 40) + 20), 10, 20, 20, 0.01, lifePoint, power, defense),
	  xpValue(xpValue)
{
	Level::enemies.insert(this);
	this->timeSinceLastShot = 0;
}

Enemy::~Enemy()
{
	Level::enemies.erase(this);
}

void Enemy::update()
{
	this->checkCollisions();
	this->timeSinceLastShot += Game::frameTime;
	if (this->timeSinceLastShot > 1500000000)
	{
		this->shoot();
	}

	if (this->lifePoints <= 0)
	{
		this->die();
	}
	this->moveDown();
	if (this->rect.y > Graphics::screenHeight)
	{
		this->~Enemy();
	}
}

void Enemy::die()
{
	this->~Enemy();
	Player::instance->gainExperience(this->xpValue);
}

void Enemy::shoot()
{
	new Projectile(255, 0, 0, this->getX(), this->getY() + this->height, 1, this->power, 0.02f);
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
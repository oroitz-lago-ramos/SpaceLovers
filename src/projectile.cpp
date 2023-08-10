#include <SDL2/SDL.h>
#include <iostream>
#include "character.hpp"
#include "projectile.hpp"
#include "level.hpp"
#include "graphics.hpp"
#include "enemy.hpp"
#include "player.hpp"

Projectile::Projectile(int r, int g, int b, int x, int y, int direction, int power, float speed)
	: Character(r, g, b, x, y, 5, 5, speed),
	  direction(direction), power(power)

{
	Level::projectiles.insert(this);
}

Projectile::~Projectile()
{
	Level::projectiles.erase(this);
}

void Projectile::update()
{
	if (this->direction == 1)
		this->moveDown();
	else if (this->direction == -1)
		this->moveUp();

	this-> checkCollisions();
	
	if (this->rect.y > Graphics::screenHeight || this->rect.y < 0 || this->rect.x > Graphics::screenWidth || this->rect.x < 0)
	{
		this->~Projectile();
	}
}

void Projectile::checkCollisions()
{
	for (auto enemy : std::set<Enemy *>(Level::enemies))
	{	
		if (SDL_HasIntersection(&this->rect, &enemy->rect))
		{
			enemy->takeDamage(1);
			this->~Projectile();

			return;
		}
	}
	if (SDL_HasIntersection(&this->rect, &Player::instance->rect))
	{
		Player::instance->takeDamage(this->power);
		this->~Projectile();

		return;
	}
}
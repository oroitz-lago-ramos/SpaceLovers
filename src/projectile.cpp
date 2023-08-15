#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <iostream>
#include "character.hpp"
#include "projectile.hpp"
#include "level.hpp"
#include "graphics.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include <set>
#include <climits>

Projectile::Projectile(int r, int g, int b, int x, int y, int power, float speed, float dirX, float dirY, bool target)
	: Character(r, g, b, x, y, 5, 5, speed, dirX, dirY),
	  direction(0), power(power), target(nullptr)
{
	SDL_Surface *projectile = IMG_Load("assets/flame1.png");
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, projectile);
	if (target)
	{
		// Enemy *enemy = nullptr;
		// int distance = INT_MAX;
		// for (auto e : Level::enemies)
		// {
		// 	double dx = this->getX() - e->getX();
		// 	double dy = this->getY() - e->getY();
		// 	int currentDist = std::sqrt(dx * dx + dy * dy);
		// 	if (currentDist < distance)
		// 	{
		// 		distance = currentDist;
		// 		enemy = e;
		// 	}
		// }
		// this->target = enemy;
		this->findTarget();
	}
	Level::projectiles.insert(this);
}
Projectile::Projectile(int r, int g, int b, int x, int y, int direction, int power, float speed)
	: Character(r, g, b, x, y, 5, 5, speed),
	  direction(direction), power(power), target(nullptr)

{
	SDL_Surface *projectile = IMG_Load("assets/flame1.png");
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, projectile);
	Level::projectiles.insert(this);
}

void Projectile::findTarget()
{
	Enemy *enemy = nullptr;
	int distance = INT_MAX;
	for (auto e : std::set<Enemy*>(Level::enemies))
	{
		double dx = this->getX() - e->getX();
		double dy = this->getY() - e->getY();
		int currentDist = std::sqrt(dx * dx + dy * dy);
		if (currentDist < distance)
		{
			distance = currentDist;
			enemy = e;
		}
	}
	this->target = enemy;
}

Projectile::Projectile(int r, int g, int b, int x, int y, int power, float speed, float dirX, float dirY)
	: Character(r, g, b, x, y, 5, 5, speed, dirX, dirY),
	  direction(0), power(power), target(nullptr)
{
	SDL_Surface *projectile = IMG_Load("assets/flame1.png");
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, projectile);
	Level::projectiles.insert(this);
}

Projectile::~Projectile()
{
	Level::projectiles.erase(this);
}

void Projectile::update()
{

	if (this->target)
	{
		// this->findTarget();
		double dx = this->getX() - this->target->getX();
		double dy = this->getY() - this->target->getY();
		double angle = std::atan2(dy, dx);
		this->dirX = -std::cos(angle);
		this->dirY = -std::sin(angle);
		this->target = nullptr;
	}

	if (this->direction == 1)
		this->moveDown();
	else if (this->direction == -1)
		this->moveUp();
	else if (this->direction == 0)
		this->move();

	this->checkCollisions();

	if (this->rect.y > Graphics::screenHeight || this->rect.y < 0 || this->rect.x > Graphics::screenWidth || this->rect.x < 0)
	{
		this->~Projectile();
	}
}

// On verifie les collision des projectiles.
//(La première condition verifie si on touche un ennemi, la deuxième, si un ennemi nous touche).
void Projectile::checkCollisions()
{
	for (auto enemy : std::set<Enemy *>(Level::enemies))
	{
		if (SDL_HasIntersection(&this->rect, &enemy->rect))
		{
			enemy->takeDamage(this->power);
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
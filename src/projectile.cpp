#include <SDL2/SDL.h>
#include <iostream>
#include "character.hpp"
#include "projectile.hpp"
#include "level.hpp"
#include "graphics.hpp"
#include "enemy.hpp"

Projectile::Projectile(int r, int g, int b, int x, int y, int direction)
	: Character(r, g, b, x, y, 5, 5, 1.0f),
	  direction(direction)

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


	for (auto enemy : std::set<Enemy *>(Level::enemies))
	{
		if (SDL_HasIntersection(&this->rect, &enemy->rect))
		{
			// enemy->takeDamage(1);
			// std::cout << "projectile collision!" << std::endl;
			
			return;
		}
	}


	if (this->rect.y > Graphics::screenHeight || this->rect.y < 0 || this->rect.x > Graphics::screenWidth || this->rect.x < 0)
	{
		this->~Projectile();
	}
}
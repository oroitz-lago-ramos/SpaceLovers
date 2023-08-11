#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>

#include "entity.hpp"
#include "graphics.hpp"
#include "inGameItem.hpp"
#include "level.hpp"
#include "player.hpp"

InGameItem::InGameItem()
	: Character(30, 200, 20, rand() % Graphics::screenWidth, 10, 10, 10, 0.02f)
{
	Level::powerUps.insert(this);
}

InGameItem::~InGameItem()
{
	Level::powerUps.erase(this);
}

void InGameItem::update()
{
	this->checkCollisions();
	this->moveDown();
	if (this->rect.y > Graphics::screenHeight)
	{
		this->~InGameItem();
	}
}

void InGameItem::checkCollisions()
{
	if (SDL_HasIntersection(&this->rect, &Player::instance->rect))
	{
		/* switch (powerUp)
		{
		case :
			//code ici
			break;

		default:
			break;
		} */

		// this->heal();
		this->bomb();
		this->~InGameItem();
	}
}

void InGameItem::heal()
{
	if (Player::instance->lifePoints < Player::instance->maxLifePoints - 20)
	{
		Player::instance->lifePoints += 20;
	}
}

void InGameItem::speedUp()
{
	/* Comment faire les 10 secondes?
	this-> itemTimer = 0;
	float tempSpeed = Player::instance->speed;
	while(itemTimer < Xvaleur)
	{
		Player::instance->speed = 0.05f;
	}
	*/
}

void InGameItem::powerBoost()
{
	Player::instance->power = 10;
}

void InGameItem::bomb()
{
	// for (auto enemy : std::set<Enemy *>(Level::enemies))
	// {
	//     enemy->die();
	// }
}

void InGameItem::changeNumberOfProjectiles(int number)
{
	Player::instance->numberOfProjectiles = number;
}

void InGameItem::changeReloadSpeed()
{
}
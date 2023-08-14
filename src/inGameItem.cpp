#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>

#include "entity.hpp"
#include "graphics.hpp"
#include "inGameItem.hpp"
#include "level.hpp"
#include "player.hpp"

InGameItem::InGameItem(PowerUp powerUp)
	: Character(30, 200, 20, rand() % Graphics::screenWidth, 10, 10, 10, 0.02f),
	  powerUp(powerUp)
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
		this->powerUpAction();
		this->~InGameItem();
	}
}

void InGameItem::powerUpAction()
{
	switch (this->powerUp)
	{
	case HEAL:
		this->heal();
		break;

	case BOMB:
		this->bomb();
		break;

	default:
		break;
	}
}

void InGameItem::heal()
{

	int heal = 20;
	if (Player::instance->lifePoints < Player::instance->maxLifePoints - heal)
	{
		Player::instance->lifePoints += 20;
	}
}

void InGameItem::speedUp()
{
	Player::instance->speed += 0.02f
	// ou Player::instance->speed = a qqchse
}

void InGameItem::powerBoost()
{
	Player::instance->power += 10;
}

void InGameItem::bomb()
{
	for (auto enemy : std::set<Enemy *>(Level::enemies))
	{
		enemy->die();
	}
}

void InGameItem::changeNumberOfProjectiles(int number)
{
	Player::instance->numberOfProjectiles = number;
}

void InGameItem::changeReloadSpeed()
{
	Player::instance->reloadSpeed = 100000;
}
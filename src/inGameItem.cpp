#include <iostream>
#include <SDL2/SDL.h>
#include <functional>

#include "entity.hpp"
#include "graphics.hpp"
#include "inGameItem.hpp"
#include "level.hpp"
#include "player.hpp"
#include "game.hpp"

InGameItem::InGameItem(int powerUp)
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
		(this->*boostFonctions[this->powerUp])();
		this->~InGameItem();
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
	std::cout << "JE pends speedup" << std::endl;

	Player::instance->playerBoost.push_back((PlayerBoost){10000000000ull, 0ull, []()
														  { Player::instance->speed -= 0.02f; }});
	Player::instance->speed += 0.02f;
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

void InGameItem::changeNumberOfProjectiles()
{
	Player::instance->numberOfProjectiles += rand() % 2 + 1;
}

void InGameItem::changeReloadSpeed()
{
	Player::instance->reloadSpeed = 10000000;
}
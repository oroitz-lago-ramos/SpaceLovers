#include <iostream>
#include <SDL2/SDL.h>
#include <functional>

#include "entity.hpp"
#include "graphics.hpp"
#include "inGameItem.hpp"
#include "level.hpp"
#include "player.hpp"
#include "game.hpp"
typedef void (InGameItem::*myfunc)();

myfunc InGameItem::boostFonctions[NUMBER_OF_BOOST] = {&InGameItem::speedUp};
InGameItem::InGameItem(int powerUp)
	: Character(30, 200, 20, rand() % Graphics::screenWidth, 10, 10, 10, 0.02f),
	  powerUp(powerUp)
{
	this->go = InGameItem::boostFonctions[powerUp];
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
	// std::cout << "methode" << std::endl;
	if (SDL_HasIntersection(&this->rect, &Player::instance->rect))
	{
		std::cout << this->powerUp << std::endl;
		std::cout << (void *)(this->*boostFonctions[this->powerUp]) << std::endl;

		// (this->*boostFonctions[this->powerUp])();
		(this->*go)();
		std::cout << "ligne 40 lets goooo" << std::endl;
		this->~InGameItem();
		std::cout << "La fonction check collisions est finie" << std::endl;
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
	Player::instance->playerBoost.push_back((PlayerBoost){10000000000ull, 0ull, []()
														  { Player::instance->power -= 10; }});
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
	Player::instance->playerBoost.push_back((PlayerBoost){10000000000ull, 0ull, []()
														  { Player::instance->numberOfProjectiles = 1; }});
	Player::instance->numberOfProjectiles += rand() % 2 + 1;
}

void InGameItem::changeReloadSpeed()
{
	std::cout << "Je lance la fonction reload speed" << std::endl;
	Player::instance->playerBoost.push_back((PlayerBoost){10000000000ull, 0ull, []()
														  { Player::instance->reloadSpeed += 250000000; std::cout << "Je remet mon reload speed a zero" << std::endl;}});
	Player::instance->reloadSpeed -= 250000000;
}
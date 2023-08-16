#include <iostream>
#include <SDL2/SDL.h>
#include <functional>

#include "entity.hpp"
#include "graphics.hpp"
#include "inGameItem.hpp"
#include "level.hpp"
#include "player.hpp"
#include "game.hpp"
typedef void (*myfunc)();

void heal()
{
	int heal = 20;
	if (Player::instance->lifePoints < Player::instance->maxLifePoints - heal)
	{
		Player::instance->lifePoints += 20;
	}
}

void statsBoost()
{
	Player::instance->playerBoost.insert(new PlayerBoost(10000000000ull, 0ull, []()
														  { Player::instance->power -= 10;
														  	Player::instance->speed -= 0.02f; }));
	Player::instance->power += 10;
	Player::instance->speed += 0.02f;
}

void changeNumberOfProjectiles()
{
	Player::instance->playerBoost.insert(new PlayerBoost(10000000000ull, 0ull, []()
														  { Player::instance->numberOfProjectiles = 1; }));
	Player::instance->numberOfProjectiles += rand() % 2 + 1;
}

void bomb()
{
	for (auto enemy : std::set<Enemy *>(Level::enemies))
	{
		enemy->die();
	}
}

myfunc InGameItem::boostFonctions[NUMBER_OF_BOOST] = {
	&heal,
	&statsBoost,
	&changeNumberOfProjectiles,
	&bomb};
InGameItem::InGameItem(int powerUp)
	: Character(30, 200, 20, rand() % Graphics::screenWidth, 10, 10, 10, 0.02f),
	  powerUp(powerUp)
{
	this->destroyTexture = false;
	this->texture = Graphics::boosts[this->powerUp];
	SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
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
	if (SDL_HasIntersection(&this->rect, &Player::instance->rect))
	{
		std::cout << this->powerUp << std::endl;
		(*this->go)();
		this->~InGameItem();
	}
}

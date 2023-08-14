#ifndef INGAMEITEM_HPP
#define INGAMEITEM_HPP
#define NUMBER_OF_BOOST 1

#include <SDL2/SDL.h>
#include "entity.hpp"
#include "character.hpp"
#include <iostream>

enum PowerUp
{
	HEAL,
	BOMB,
	RELOAD_SPEED,
	SPEED_UP,
	POWER_BOOST,
	MULTIPLE_PROJECTILE,

	// DEFENSE_UP,
	// SHIELD,
};

class InGameItem : public Character
{
	typedef void (InGameItem::*myfunc)();

public:
	InGameItem(int powerUp);
	~InGameItem();
	void update();
	int powerUp;
	//myfunc boostFonctions[NUMBER_OF_BOOST] = {&InGameItem::heal, &InGameItem::bomb, &InGameItem::changeReloadSpeed, &InGameItem::speedUp, &InGameItem::powerBoost, &InGameItem::changeNumberOfProjectiles};
	myfunc boostFonctions[1] = {&InGameItem::speedUp};
private:
	void checkCollisions();

	void heal();
	void bomb();
	void changeNumberOfProjectiles();
	void changeReloadSpeed();
	void speedUp();
	void powerBoost();

	// void (*fonctions[])();
};

#endif
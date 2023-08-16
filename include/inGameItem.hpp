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
	static myfunc boostFonctions[NUMBER_OF_BOOST];
	myfunc go;
	//myfunc boostFonctions[NUMBER_OF_BOOST] = {&InGameItem::heal, &InGameItem::bomb, &InGameItem::changeReloadSpeed, &InGameItem::speedUp, &InGameItem::powerBoost, &InGameItem::changeNumberOfProjectiles};

private:
	void checkCollisions();

	static void heal();
	static void bomb();
	static void changeNumberOfProjectiles();
	static void changeReloadSpeed();
	static void speedUp();
	static void powerBoost();

	// void (*fonctions[])();
};

#endif
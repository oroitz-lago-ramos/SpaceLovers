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
	SPEED_UP,
	DEFENSE_UP,
	SHIELD,
	DOUBLE_PROJECTILE,
	RELOAD_SPEED,
	BOMB
};



class InGameItem : public Character
{
	typedef void (InGameItem::*myfunc)();
public:
	InGameItem(int powerUp);
	~InGameItem();
	void update();
	int powerUp;
	//myfunc boostFonctions[NUMBER_OF_BOOST] = {&InGameItem::heal,&InGameItem::bomb,&InGameItem::changeReloadSpeed,&InGameItem::speedUp,&InGameItem::powerBoost};
	myfunc boostFonctions[NUMBER_OF_BOOST] = {&InGameItem::changeNumberOfProjectiles};

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
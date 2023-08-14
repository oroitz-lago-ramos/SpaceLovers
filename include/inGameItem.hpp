#ifndef INGAMEITEM_HPP
#define INGAMEITEM_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"
#include "character.hpp"

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
public:
	InGameItem(PowerUp powerUp);
	~InGameItem();
	void update();
	PowerUp powerUp;

private:
	void checkCollisions();
	void powerUpAction();

	void heal();
	void bomb();
	void changeNumberOfProjectiles(int number);
	void changeReloadSpeed();
	void speedUp();
	void powerBoost();

	// void (*fonctions[])();
};

#endif
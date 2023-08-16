#ifndef INGAMEITEM_HPP
#define INGAMEITEM_HPP
#define NUMBER_OF_BOOST 4

#include <SDL2/SDL.h>
#include "entity.hpp"
#include "character.hpp"
#include <iostream>

enum PowerUp
{
	HEAL,
	STATS_BOOST,
	MULTIPLE_PROJECTILE,
	BOMB
};

class InGameItem : public Character
{
	typedef void (*myfunc)();

public:
	InGameItem(int powerUp);
	~InGameItem();
	void update();
	int powerUp;
	static myfunc boostFonctions[NUMBER_OF_BOOST];
	myfunc go;

private:
	void checkCollisions();
};

#endif
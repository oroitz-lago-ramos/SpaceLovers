#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SDL2/SDL.h>

#include "character.hpp"

class Projectile : public Character
{
public:
	Projectile(int r, int g, int b, int x, int y, int direction);
	~Projectile();
	
	void update();
	int direction;
};

#endif
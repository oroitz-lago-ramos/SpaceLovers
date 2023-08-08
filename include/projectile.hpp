#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SDL2/SDL.h>

#include "character.hpp"

class Projectile : public Character
{
	Projectile(int r, int g, int b, SDL_Rect rect);
	~Projectile();
	
	void update();
};

#endif
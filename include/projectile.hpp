#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SDL2/SDL.h>

#include "character.hpp"
#include "enemy.hpp"

class Projectile : public Character
{
public:
	Projectile(int r, int g, int b, int x, int y, int direction, int power, float speed);
	Projectile(int r, int g, int b, int x, int y, int power, float speed, float dirX, float dirY);
	Projectile(int r, int g, int b, int x, int y, int power, float speed, float dirX, float dirY, bool target, int pierce);
	~Projectile();

	void update();
	int direction;

	int power;
	Enemy *target;
	int pierce;
	Enemy *targetHit[2];
	int hits;

private:
	void checkCollisions();
	void findTarget();
};

#endif
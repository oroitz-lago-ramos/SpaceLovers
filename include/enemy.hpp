#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL2/SDL.h>
#include "character.hpp"

class Enemy : public Character
{
public:
	Enemy(float power, float defense, float lifePoint, float xpValue);
	~Enemy();
	void update();

	void die();
	void shoot();

	float xpValue;

private:
	void checkCollisions();
};

#endif
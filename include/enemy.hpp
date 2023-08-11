#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL2/SDL.h>
#include "character.hpp"

class Enemy : public Character
{
public:
	Enemy(float lifePoints, float power, float defense, float xpValue);
	Enemy(float lifePoints, float power, float defense, float xpValue, float shield);
	~Enemy();
	void update();

	void die();
	void shoot();

	float xpValue;
	float shield;

private:
	void checkCollisions();
};

#endif
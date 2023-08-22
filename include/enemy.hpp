#ifndef ENEMY_HPP
#define ENEMY_HPP

#define ISBOSS 1
#define ATTACKLASER 2
#define ATTACKSWEEP 4

#include <SDL2/SDL.h>
#include <set>
#include "character.hpp"
#include "attack.hpp"

class Attack;

class Enemy : public Character
{
public:
	Enemy(float lifePoints, float power, float defense, float xpValue);
	Enemy(float lifePoints, float power, float defense, float xpValue, float shield, int flags);
	~Enemy();
	void update();

	void die();
	void shoot();

	float xpValue;
	int flags;
	std::set<Attack *> attacks;

private:
	void checkCollisions();
};

#endif
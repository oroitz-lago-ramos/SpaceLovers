#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

class Character : public Entity
{
public:
	Character(int r, int g, int b, int x, int y, int width, int height, float speed, float lifePoints, float power, float defense);
	Character(int r, int g, int b, int x, int y, int width, int height, float speed);
	~Character();

	float speed;
	float lifePoints;
	float maxLifePoints;
	float power;
	float defense;

	unsigned long long int timeSinceLastShot;

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	void takeDamage(float damage);

private:
};

#endif
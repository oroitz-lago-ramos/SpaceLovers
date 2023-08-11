#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

class Character : public Entity
{
public:
	Character(int r, int g, int b, int x, int y, int width, int height, float speed, float lifePoints, int power, float defense);
	Character(int r, int g, int b, int x, int y, int width, int height, float speed);
	Character(int r, int g, int b, int x, int y, int width, int height, float speed, float dirX, float dirY);
	~Character();
	void move();
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	float speed;
	float dirX;
	float dirY;
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
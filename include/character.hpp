#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

class Character : public Entity
{
public:
	Character(int r, int g, int b, int x, int y, int width, int height, float speed, float lifePoints);
	Character(int r, int g, int b, int x, int y, int width, int height, float speed);
	~Character();
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	float speed;

	float lifePoints;
	float maxLifePoints;
	unsigned long long int timeSinceLastShot;

	void takeDamage(float damage);
	void die();

    float lifePoints;
    float maxLifePoints;
    unsigned long long int timeSinceLastShot;
    
    void takeDamage(float damage);
    void die();
private:
};

#endif
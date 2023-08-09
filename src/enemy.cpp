#include <iostream>
#include "functional"
#include <SDL2/SDL.h>

#include "enemy.hpp"
#include "level.hpp"
#include "character.hpp"
#include "graphics.hpp"
#include "game.hpp"

Enemy::Enemy(int power, int defense)
    : Character(255, 0, 0, rand()%Graphics::screenWidth, 10, 20, 20, 0.01),
    power(power), defense(defense)
{
    Level::enemies.insert(this);
    this->lifePoints = 1;
    this -> timeSinceLastShot = 0;
}

Enemy::~Enemy()
{
    Level::enemies.erase(this);
}

void Enemy::update()
{
    this -> timeSinceLastShot += Game::frameTime;
    this -> shoot();

    if (this->lifePoints <= 0)
    {
        this->die();
    }
    this -> moveDown();
    if (this -> rect.y > Graphics::screenHeight)
    {
        this -> ~Enemy();
    }
}

void Enemy::die()
{
   this->~Enemy(); 
}

void Enemy::shoot()
{
    if (this -> timeSinceLastShot > 500000000)
	{
		new Projectile(255, 0, 0, this->getX(), this->getY() + this->height, 1, this->power);
		this -> timeSinceLastShot = 0;
	}
}
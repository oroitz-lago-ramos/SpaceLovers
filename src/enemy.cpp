#include <iostream>
#include "functional"
#include <SDL2/SDL.h>

#include "enemy.hpp"
#include "level.hpp"
#include "character.hpp"
#include "graphics.hpp"

Enemy::Enemy(int power, int defense)
    : Character(255, 0, 0, rand()%Graphics::screenWidth, 10, 20, 20, 0.01),
    power(power), defense(defense)
{
    Level::enemies.insert(this);
}

Enemy::~Enemy()
{
    Level::enemies.erase(this);
}

void Enemy::update()
{
    this -> moveDown();
    if (this -> rect.y > Graphics::screenHeight)
    {
        this -> ~Enemy();
    }
}
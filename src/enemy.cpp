#include <iostream>
#include "functional"
#include <SDL2/SDL.h>

#include "enemy.hpp"
#include "level.hpp"
#include "character.hpp"
#include "graphics.hpp"

Enemy::Enemy(int power, int defense)
    : Character(255, 0, 0, {rand()%Graphics::screenWidth, 0, 20, 20}, 0.1),
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
}
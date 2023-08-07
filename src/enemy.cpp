#include <iostream>
#include "functional"
#include <SDL2/SDL.h>

#include "enemy.hpp"
#include "graphics.hpp"

Enemy::Enemy(int power, int speed, int defense, SDL_Rect rect)
    : Entity(power % 256, speed %256, defense %256, rect),
    power(power), speed(speed), defense(defense)
{
    Graphics::enemys.insert(this);
    std::cout << "Button constructor called!" << std::endl;
}

Enemy::~Enemy()
{
    Graphics::enemys.erase(this);
}
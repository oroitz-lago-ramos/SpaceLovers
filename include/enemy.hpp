#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

class Enemy:public Entity
{
public:
    Enemy(int power, int speed, int defense, SDL_Rect rect);
    ~Enemy();

    int power;
    int speed;
    int defense;
};

#endif
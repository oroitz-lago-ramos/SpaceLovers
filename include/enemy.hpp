#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL2/SDL.h>
#include "character.hpp"

class Enemy:public Character
{
public:
    Enemy(int power, int defense, float lifePoint, float xpValue);
    ~Enemy();
    void update();

    void die();
    void shoot();

    int power;
    int defense;
    float xpValue;

private:
    void checkCollisions();
};


#endif
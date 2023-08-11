#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL2/SDL.h>
#include "character.hpp"

class Enemy:public Character
{
public:
    Enemy(int power, int defense);
    ~Enemy();
    void update();

    void die();
    void shoot();

    int power;
    float defense;
private:
    void checkCollisions();
};


#endif
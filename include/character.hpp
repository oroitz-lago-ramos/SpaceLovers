#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

class Character : public Entity
{
public:
    Character(int r, int g, int b, SDL_Rect rect);
    ~Character();
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
};

#endif
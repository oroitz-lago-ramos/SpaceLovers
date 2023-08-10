#ifndef INGAMEITEM_HPP
#define INGAMEITEM_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

class InGameItem : public Character
{
public:
    InGameItem();
    ~InGameItem();
    void update();

private:
    void checkCollisions();

    void heal();
    void speedUp();
};

#endif
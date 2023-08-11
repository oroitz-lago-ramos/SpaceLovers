#ifndef INGAMEITEM_HPP
#define INGAMEITEM_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

//enum PowerUp {HEAL, SPEEDUP};
class InGameItem : public Character
{
public:
    InGameItem(/*PowerUp powerUp*/);
    ~InGameItem();
    void update();
    //PowerUp powerUp;
private:
    void checkCollisions();

    void heal();
    void speedUp();
};

#endif
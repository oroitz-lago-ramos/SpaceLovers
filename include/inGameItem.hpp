#ifndef INGAMEITEM_HPP
#define INGAMEITEM_HPP

#include <SDL2/SDL.h>
#include "entity.hpp"

// enum PowerUp {HEAL, SPEEDUP, DEFENSEUP, SHIELD, DOUBLE_PROJECTILE, RELOAD_SPEED, BOMB};
class InGameItem : public Character
{
public:
    InGameItem(/*PowerUp powerUp*/);
    ~InGameItem();
    void update();
    // PowerUp powerUp;
private:
    void checkCollisions();

    void heal();
    void bomb();
    void changeNumberOfProjectiles(int number);
    void changeReloadSpeed();
    void speedUp();
    void powerBoost();    
};

#endif
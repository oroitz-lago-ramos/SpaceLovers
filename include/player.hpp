#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"

class Player : public Character
{
public:
    Player();
    ~Player();
    void update(int direction);
    void shoot();
    
private:
    
};

#endif
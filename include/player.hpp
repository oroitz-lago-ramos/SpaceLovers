#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"

class Player : public Character
{
public:
    Player();
    ~Player();
    
	static Player *instance;

	void update();
    void shoot();
    void die();

    float experience;

    int numberOfProjectiles;
private:
};

#endif
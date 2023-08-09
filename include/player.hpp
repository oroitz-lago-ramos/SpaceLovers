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
    
    

private:
    
};

#endif
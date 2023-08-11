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
	void gainExperience(float experience);

	float experience;

	int numberOfProjectiles;
	long long int unsigned reloadSpeed;

private:
};

#endif
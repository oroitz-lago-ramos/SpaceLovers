#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <functional>
#include <set>

#include "character.hpp"
#include "playerBoost.hpp"

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
	float projectileSpeed;
	int pierce;
	int bestLevel;

	std::set<PlayerBoost *> playerBoost;

private:
};

#endif
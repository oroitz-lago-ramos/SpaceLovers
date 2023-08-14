#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <functional>

#include "character.hpp"

typedef struct PlayerBoost
{
	long long unsigned int powerUpDuration;
	long long unsigned int timeSincePowerUpStart;

	std::function<void()> onEnd;
} PlayerBoost;

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

	std::vector<PlayerBoost> playerBoost;

private:
};

#endif
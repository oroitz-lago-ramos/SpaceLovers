#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SDL2/SDL.h>
#include <set>
#include <string>

#include "enemy.hpp"
#include "projectile.hpp"
#include "text.hpp"
#include "inGameItem.hpp"

class Level
{

public:
	Level();
	~Level();
	static std::set<Projectile *> projectiles;
	static std::set<Enemy *> enemies;
	static std::set<InGameItem *> powerUps;
	static Level *instance;
	std::string count;
	Text *timer;
	Text *levelRunning;
	Text *xpTotal;
	Text *fps;
	void update();
	void countdown();
	void initPlayer();

	long long unsigned int timeSinceLastSpawn;
	long long unsigned int timeSinceLastPoweUp;
	long long unsigned int timeSinceLastBoss;
	long long unsigned int nanoSecond;
	float difficulty;
	int boardLevel;
	void setCurrentLvl(int currentLvl);
	int getCurrentLvl();
	
private:
	int currentLvl;
};

#endif
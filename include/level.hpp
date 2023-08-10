#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SDL2/SDL.h>
#include <set>

#include "enemy.hpp"
#include "projectile.hpp"
#include "text.hpp"

class Level
{
public:
	Level();
	~Level();
	static std::set<Projectile *> projectiles;
	static std::set<Enemy *> enemies;
	static Level *instance;
	long long int nanoSecond;
	std::string count;
	Text timer;
	void update();
	void countdown();


	unsigned long long int timeSinceLastSpawn;
};


#endif
#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SDL2/SDL.h>
#include <set>

#include "enemy.hpp"
#include "projectile.hpp"

class Level
{
public:
	Level();
	~Level();
	static std::set<Projectile *> projectiles;
	static std::set<Enemy *> enemies;
};

#endif
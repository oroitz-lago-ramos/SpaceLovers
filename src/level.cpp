#include <SDL2/SDL.h>

#include "level.hpp"
#include "enemy.hpp"
#include "projectile.hpp"

std::set<Projectile *> Level::projectiles = {};
std::set<Enemy *> Level::enemies = {};

Level::Level()
{
}

Level::~Level()
{
	for (auto projectile : projectiles)
	{
		projectiles.erase(projectile);
	}
	for (auto enemy : enemies)
	{
		enemies.erase(enemy);
	}
}
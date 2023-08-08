#include <SDL2/SDL.h>

#include "level.hpp"
#include "enemy.hpp"
#include "projectile.hpp"

std::set<Projectile *> Level::projectiles = {};
std::set<Enemy *> Level::enemies = {};

Level::Level()
	: timeSinceLastSpawn(0)
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

void Level::update()
{
	this -> timeSinceLastSpawn ++;
	if (this -> timeSinceLastSpawn > 10000)
	{
		new Enemy(10, 10);
		this -> timeSinceLastSpawn = 0;
	}
}

// void Level::render()
// {
// 	for (auto enemy : std::set<Enemy *>(Level::enemies))
//     {
//         enemy->update();
//         enemy->render();
//     }

//     for (auto projectile : std::set<Projectile *>(Level::projectiles))
//     {
//         projectile->update();
//         projectile->render();
//     }
// }
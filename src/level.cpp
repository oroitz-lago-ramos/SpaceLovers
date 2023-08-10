#include <SDL2/SDL.h>
#include <iostream>

#include "level.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "game.hpp"

std::set<Projectile *> Level::projectiles = {};
std::set<Enemy *> Level::enemies = {};
Level* Level::instance = nullptr;

Level::Level()
	: timeSinceLastSpawn(0), nanoSecond(60000000000)
{
	Level::instance = this;
	Player::instance->lifePoints = Player::instance->maxLifePoints;
	this -> timer = new Text(255, 255, 255, Graphics::windowWidth - 100, 100, 100, 75, "60", "Kichenset.otf", 24);
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
	Game::currentState = MENU;
}

void Level::update()
{
	this -> timeSinceLastSpawn += Game::frameTime;
	if (this -> timeSinceLastSpawn > 2000000000)
	{
		new Enemy(10, 10);
		this -> timeSinceLastSpawn = 0;
	}
	this -> countdown();
	this -> timer->render();
}

void Level::countdown()
{
	this->nanoSecond -= Game::frameTime;
	int second = Level::nanoSecond / 1000000000;
	if (second >= 0)
	{
		this -> count = std::to_string(second);
		this -> timer->textUpdate(this -> count.c_str());
	}
}


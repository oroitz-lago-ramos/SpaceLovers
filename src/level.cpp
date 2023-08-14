#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <set>
#include <iostream>
#include <stdio.h>
#include <set>

#include "level.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "game.hpp"

std::set<Projectile *> Level::projectiles = {};
std::set<Enemy *> Level::enemies = {};
std::set<InGameItem *> Level::powerUps = {};
Level *Level::instance = nullptr;

Level::Level()
	: timeSinceLastSpawn(0), timeSinceLastPoweUp(0), timeSinceLastBoss(0), nanoSecond(60000000000), currentLvl(1), difficulty(1)
{
	Level::instance = this;
	Player::instance->lifePoints = Player::instance->maxLifePoints;
	char str[15];
	snprintf(str, 15, "Niveau %03d", this->currentLvl);
	char strXp[15];
	snprintf(strXp, 15, "Xp: %07.0f", Player::instance->experience);
	this->timer = new Text(0, 250, 200, Graphics::windowWidth - 100, 200, 100, 75, "60", "Kichenset.otf", 24);
	this->levelRunning = new Text(0, 250, 200, Graphics::windowWidth - 100, 100, 150, 75, str, "Kichenset.otf", 24);
	this->xpTotal = new Text(0, 250, 200, Graphics::windowWidth - 100, Graphics::screenHeight - 150, 150, 75, strXp, "Kichenset.otf", 24);
}

Level::~Level()
{
	for (auto projectile : std::set<Projectile *>(this->projectiles))
	{
		projectiles.erase(projectile);
	}
	for (auto enemy : std::set<Enemy *>(this->enemies))
	{
		enemies.erase(enemy);
	}
	Game::currentState = MENU;
	Game::inputs = 0;
}

void Level::update()
{
	this->timeSinceLastSpawn += Game::frameTime;
	this->timeSinceLastPoweUp += Game::frameTime;
	this->timeSinceLastBoss += Game::frameTime;

	if (this->timeSinceLastSpawn > 2000000000)
	{
		new Enemy(1 * this->difficulty, 1 * this->difficulty, 1 * this->difficulty, 1 * this->difficulty);
		this->timeSinceLastSpawn = 0;
	}

	if (this->timeSinceLastBoss > 2000000000)
	{
		new Enemy(20 * this->difficulty, 20 * this->difficulty, 20 * this->difficulty, 10 * this->difficulty, 20 * this->difficulty, ISBOSS | (1 << (rand()%2+1)));
		this->timeSinceLastBoss = 0;
	}

	if (this->timeSinceLastPoweUp > 2000000000)
	{
		new InGameItem(rand()%NUMBER_OF_BOOST);
		this->timeSinceLastPoweUp = 0;
	}
	this->countdown();
	this->timer->render();
	this->levelRunning->render();
	this->xpTotal->render();
}

void Level::countdown()
{
	this->nanoSecond -= Game::frameTime;
	int second = Level::nanoSecond / 1000000000;
	if (second >= 0)
	{
		this->count = std::to_string(second);
		this->timer->textUpdate(this->count.c_str());
	}
	if (second == 0)
	{
		this->nanoSecond = 60000000000;
		this->currentLvl++;
		this->difficulty *= 1.1;
		char str[15];
		snprintf(str, 15, "Niveau %03d", this->currentLvl);
		this->levelRunning->textUpdate(str);
	}
}

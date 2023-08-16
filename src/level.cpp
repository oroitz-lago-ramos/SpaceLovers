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
	: timeSinceLastSpawn(0), timeSinceLastPoweUp(0), timeSinceLastBoss(0), nanoSecond(30000000000), currentLvl(1), difficulty(1), boardLevel(1)
{
	Level::instance = this;
	char str[15];
	snprintf(str, 15, "Niveau %03d", this->getCurrentLvl());
	char strXp[15];
	snprintf(strXp, 15, "Xp: %07.0f", Player::instance->experience);
	this->timer = new Text(0, 250, 200, Graphics::windowWidth - 100, 200, 100, 75, "60", "Kichenset.otf", 24);
	this->levelRunning = new Text(0, 250, 200, Graphics::windowWidth - 100, 100, 150, 75, str, "Kichenset.otf", 24);
	this->xpTotal = new Text(0, 250, 200, Graphics::windowWidth - 100, Graphics::screenHeight - 150, 150, 75, strXp, "Kichenset.otf", 24);
	char strFps[15];
	snprintf(strFps, 15, "Fps: %04d", 1000000000 / Game::frameTime);
	this->fps = new Text(0, 250, 200, Graphics::windowWidth - 100, Graphics::screenHeight - 100, 150, 75, strFps, "Kichenset.otf", 24);
	this->initPlayer();
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
	
	if (this->timeSinceLastBoss > 26500000000)
	{
		new Enemy(20 * this->difficulty, 20 * this->difficulty, 20 * this->difficulty, 10 * this->difficulty, 20 * this->difficulty, ISBOSS | (1 << (rand() % 2 + 1)));
		this->timeSinceLastBoss = 0;
	}

	if (this->timeSinceLastPoweUp > 10000000000)
	{
		new InGameItem();
		this->timeSinceLastPoweUp = 0;
	}
	this->countdown();
	this->timer->render();
	this->levelRunning->render();
	this->xpTotal->render();
	char strFps[15];
	snprintf(strFps, 15, "Fps: %04d", 1000000000 / Game::frameTime);
	this->fps->textUpdate(strFps);
	this->fps->render();
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
		this->nanoSecond = 30000000000;
		this->setCurrentLvl(this->getCurrentLvl() + 1);
		this->boardLevel++;
		if (this->boardLevel > 10)
		{
			this->boardLevel = 1;
		}
		this->difficulty *= 1.1;
		char str[15];
		snprintf(str, 15, "Niveau %03d", this->getCurrentLvl());
		this->levelRunning->textUpdate(str);
	}
}

void Level::initPlayer()
{
	// HERE SET BASE STATS
	Player::instance->maxShield = 0;
	Player::instance->maxLifePoints = 100;
	Player::instance->power = 10;
	Player::instance->defense = 10;
	Player::instance->speed = 0.02f;
	Player::instance->reloadSpeed = 500000000;
	Player::instance->setX(Graphics::windowWidth / 2 - Player::instance->getWidth() / 2);
	Player::instance->setY(Graphics::screenHeight - Player::instance->getHeight() - 50);

	// HERE APPLY PASSIVE SKILLS
	for (auto skill : __skills)
	{
		for (int i = 0; i < skill.level; i++)
		{
			skill.effect();
		}
	}

	// HERE DO THE REST
	Player::instance->lifePoints = Player::instance->maxLifePoints;
	Player::instance->shield = Player::instance->maxShield;
}

void Level::setCurrentLvl(int currentLvl)
{
	this->currentLvl = currentLvl;
	this->timeSinceLastBoss = 0;
}

int Level::getCurrentLvl()
{
	return this->currentLvl;
}
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <fstream>
#include <sstream>

#include "button.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "enemy.hpp"
#include "level.hpp"
#include "projectile.hpp"
#include "skillTree.hpp"
#include "skillNode.hpp"
#include "rect.hpp"
#include "text.hpp"

int Game::inputs = 0;
bool Game::isRunning = true;
using namespace std;
unsigned int Game::frameTime = 0;
GameState Game::currentState = MENU;

Game::Game()
{
	// Appel de la méthode de création des boutons
	this->createButtons();
	srand(time(NULL));
	auto start = chrono::steady_clock::now();
	// this->loadGame();
	while (Game::isRunning)
	{
		auto end = chrono::steady_clock::now();
		frameTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		start = end;
		SDL_SetRenderDrawColor(Graphics::renderer, 30, 30, 30, 30);
		SDL_RenderClear(Graphics::renderer);

		if (Game::currentState == MENU)
		{
			// Boucle de gestion d'événements du menu
			this->menuEventLoop();

			// Boucle de rendu du menu
			this->menuRenderLoop();
		}

		else if (Game::currentState == GAME)
		{

			// Render loop du jeu (pas du menu)
			this->renderLoop();
			this->eventLoop();

			Level::instance->update();
		}
		else if (Game::currentState == SKILLTREE)
		{
			SkillTree::instance->render();
		}
		else if (Game::currentState == GAMEOVER)
		{
			Text *gameOver = new Text(0, 250, 200, Graphics::windowWidth / 2, 75, Graphics::windowWidth - 200, 150, "Game Over", Graphics::bigFont);
			gameOver->render();
			delete gameOver;
			char levelStr[35];
			snprintf(levelStr, 35, "Vous avez atteint le level %d", Level::instance->getCurrentLvl());
			Text *level = new Text (0, 250, 200, Graphics::windowWidth / 2, 225, Graphics::windowWidth - 200, 150, levelStr, Graphics::bigFont);
			level->render();
			delete level;
			char enemyKilled[30];
			snprintf(enemyKilled, 30, "Vous avez vaincu %d ennemis!", Level::instance->enemyKilled);
			Text *enemyKill = new Text (0, 250, 200, Graphics::windowWidth / 2, 375, Graphics::windowWidth - 200, 150, enemyKilled, Graphics::bigFont);
			enemyKill->render();
			delete enemyKill;
			char xpEarned[30];
			snprintf(xpEarned, 30, "Pour un total de %d xp!", (int)Level::instance->xpEarned);
			Text *xpEarn = new Text (0, 250, 200, Graphics::windowWidth / 2, 525, Graphics::windowWidth - 200, 150, xpEarned, Graphics::bigFont);
			xpEarn->render();
			delete xpEarn;
			static long long unsigned int gameReturn = 0;
			gameReturn += this->frameTime;
			if (gameReturn >= 5000000000)
			{
				Level::instance->~Level();
				gameReturn = 0;
			}

		}

		SDL_RenderPresent(Graphics::renderer);
	}
}

Game::~Game()
{
	this->saveGame();
	// Destruction des boutons
}

// Methode pour créer des boutons, chaque nouveau bouton doit être fait dans la méthode
void Game::createButtons()
{
	new Button(
		255, 255, 255, Graphics::screenWidth / 2, Graphics::screenHeight / 2, 100, 100, []()
		{ Game::currentState = GAME; new Level(); },
		"New game");

	new Button(
		255, 255, 255, 50, Graphics::screenHeight / 2, 100, 100, []()
		{ Game::currentState = SKILLTREE; new SkillTree(); },
		"Skill Tree");
}

void Game::eventLoop()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			Game::isRunning = false;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (this->currentState == MENU)
				this->mousebuttondown(&event);
		}
		else if (event.type == SDL_KEYDOWN)
		{
			this->keydown(&event);
		}
		else if (event.type == SDL_KEYUP)
		{
			this->keyup(&event);
		}
	}
}

void Game::menuEventLoop()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			Game::isRunning = false;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			this->mousebuttondown(&event);
		}
	}
}

void Game::mousebuttondown(SDL_Event *event)
{
	const SDL_Point point = {event->button.x, event->button.y};

	// Test tous les boutons du tableau pour voir si le &point est dans un &button->rect
	for (auto button : std::set<Button *>(Graphics::buttons))
	{
		if (SDL_PointInRect(&point, &button->rect))
		{
			button->onClick();
			break;
		}
	}
}

void Game::keydown(SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.scancode == SDL_SCANCODE_A)
	{
		Game::inputs |= BUTTON_LEFT;
	}
	else if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.scancode == SDL_SCANCODE_D)
	{
		Game::inputs |= BUTTON_RIGHT;
	}
	else if (event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_UP || event->key.keysym.scancode == SDL_SCANCODE_W)
	{
		Game::inputs |= BUTTON_SHOOT;
	}
}

void Game::keyup(SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.scancode == SDL_SCANCODE_A)
	{
		Game::inputs &= ~BUTTON_LEFT;
	}
	else if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.scancode == SDL_SCANCODE_D)
	{
		Game::inputs &= ~BUTTON_RIGHT;
	}
	else if (event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_UP || event->key.keysym.scancode == SDL_SCANCODE_W)
	{
		Game::inputs &= ~BUTTON_SHOOT;
	}
}

void Game::renderLoop()
{
	SDL_Rect backRect = {0, 0, Graphics::screenWidth, Graphics::screenHeight};
	SDL_RenderCopy(Graphics::renderer, Graphics::backgrounds[Level::instance->boardLevel - 1], NULL, &backRect);
	SDL_SetRenderDrawColor(Graphics::renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(Graphics::renderer, Graphics::screenWidth, 0, Graphics::screenWidth, Graphics::screenHeight);

	// Affichage du joueur
	this->player.update();
	this->player.render();
	this->player.renderShield();

	for (auto enemy : std::set<Enemy *>(Level::enemies))
	{
		enemy->update();
		enemy->render();
		enemy->renderShield();
	}

	for (auto projectile : std::set<Projectile *>(Level::projectiles))
	{
		projectile->update();
		projectile->render();
	}

	for (auto powerUp : std::set<InGameItem *>(Level::powerUps))
	{
		powerUp->update();
		powerUp->render();
	}

	// A partir d'ici c'est des tests vous pouvez les enlever si ça gêne ! bisous (j'enlève l'image pour pas que ça gêne pendant les gitgit)
	// SDL_Surface image = *IMG_Load("Flamme 2.png");
	// SDL_Texture* heartTexture = SDL_CreateTextureFromSurface(Graphics::renderer, &image);
	// SDL_FreeSurface(&image);

	// for (int i = 0; i < Player::instance->maxLifePoints; ++i)
	// {
	//     int heartX = 10 + i * (10 + 5);
	//     int heartY = 10;
	//     SDL_Rect heartRect = {heartX, heartY, 10, 10};
	//     SDL_RenderCopy(Graphics::renderer, heartTexture, NULL, &heartRect);
	// }
	// La j'ai essayé de faire un truc pour afficher des petites flammes à la place de la jauge mais ce sera pour plus tard j'imagine.bisous

	Rect *rect = new Rect(0, 255, 0, Graphics::windowWidth - 100, Graphics::screenHeight - 50, 152, 32);
	rect->render(true);
	delete rect;
	rect = new Rect(30, 30, 30, Graphics::windowWidth - 100, Graphics::screenHeight - 50, 150, 30);
	rect->render(true);
	delete rect;
	float lifePointsPercents = Player::instance->lifePoints / Player::instance->maxLifePoints;
	rect = new Rect(250 - 100 * lifePointsPercents, 150 * lifePointsPercents, 150 * lifePointsPercents, Graphics::windowWidth - 100, Graphics::screenHeight - 50, lifePointsPercents * 150, 30);
	rect->render(true);
	delete rect;
}

void Game::menuRenderLoop()
{
	for (auto button : std::set<Button *>(Graphics::buttons))
	{
		button->render();
	}
}

void Game::saveGame()
{
	Save saveData;
	saveData.experience = Player::instance->experience;
	for (long long unsigned int i = 0; i < __skills.size(); ++i)
	{
		t_pair saveSkill;
		saveSkill.id = i;
		saveSkill.level = __skills[i].level;
		saveData.skills.push_back(saveSkill);
	}
	std::ofstream outFile("save.dat", std::ios::binary | std::ios::out);
	if (outFile.is_open())
	{
		outFile.write(reinterpret_cast<const char *>(&saveData.experience), sizeof(float));
		int numSkills = saveData.skills.size();
		outFile.write(reinterpret_cast<const char *>(&numSkills), sizeof(int));
		for (const t_pair &skill : saveData.skills)
		{
			outFile.write(reinterpret_cast<const char *>(&skill), sizeof(t_pair));
		}

		outFile.close();
	}
	else
	{
		std::cerr << "Failed to open file for writing." << std::endl;
	}
}

bool Game::loadGame()
{
	Save saveData;

	std::ifstream inFile("save.dat", std::ios::binary | std::ios::in);
	if (inFile.is_open())
	{
		inFile.read(reinterpret_cast<char *>(&saveData.experience), sizeof(float));
		int numSkills;
		inFile.read(reinterpret_cast<char *>(&numSkills), sizeof(int));
		saveData.skills.resize(numSkills);
		for (int i = 0; i < numSkills; ++i)
		{
			inFile.read(reinterpret_cast<char *>(&saveData.skills[i]), sizeof(t_pair));
		}
		inFile.close();
		Player::instance->experience = saveData.experience;
		if (!saveData.skills.empty())
		{
			for (auto p : saveData.skills)
			{
				__skills[p.id].level = p.level;
			}
		}
	}
	else
	{
		std::cerr << "Failed to open file for reading." << std::endl;
	}
	return true;
}
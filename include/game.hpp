#ifndef GAME_HPP
#define GAME_HPP

#define BUTTON_LEFT 1
#define BUTTON_RIGHT 2
#define BUTTON_SHOOT 4

#include "graphics.hpp"
#include "player.hpp"
#include "skillNode.hpp"

#include <vector>

typedef struct save
{
	float experience;
	std::vector<t_pair> skills;
} Save;

enum GameState
{
	MENU,
	GAME,
	SKILLTREE
};

class Game
{
public:
	static int inputs;
	static bool isRunning;
	static unsigned int frameTime;
	static GameState currentState;
	Game();
	~Game();

private:
	Graphics graphics;
	Player player;
	// Methode appelée dans game.cpp pour créer les boutons
	void createButtons();
	void createTexts();
	void eventLoop();
	void menuEventLoop();
	void mousebuttondown(SDL_Event *event);
	void keydown(SDL_Event *event);
	void keyup(SDL_Event *event);
	void renderLoop();
	void menuRenderLoop();
	bool loadGame();
	void saveGame();
};

void initializeSkills();

#endif
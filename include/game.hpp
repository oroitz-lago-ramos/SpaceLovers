#ifndef GAME_HPP
#define GAME_HPP

#define BUTTON_LEFT 1
#define BUTTON_RIGHT 2
#define BUTTON_SHOOT 4

#include "graphics.hpp"
#include "player.hpp"

class Game
{
public:
	static int inputs;
    Game();
    ~Game();
    
private:
    Graphics graphics;
    Player player;
    // Methode appelée dans game.cpp pour créer les boutons
    void createButtons();
    void eventLoop();
    void mousebuttondown(SDL_Event *event);
    void keydown(SDL_Event *event);
    void keyup(SDL_Event *event);
    void renderLoop();
};

#endif
#ifndef GAME_HPP
#define GAME_HPP

#include "graphics.hpp"
#include "player.hpp"

class Game
{
public:
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
    void renderLoop();
};

#endif
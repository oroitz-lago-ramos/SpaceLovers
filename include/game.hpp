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
};

#endif
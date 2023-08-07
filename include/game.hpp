#ifndef GAME_HPP
#define GAME_HPP

#include "graphics.hpp"

class Game
{
public:
    Game();
    ~Game();
    
private:
    Graphics graphics;

    // Methode appelée dans game.cpp pour créer les boutons
    void createButtons();
    void createEnemys();
};

#endif
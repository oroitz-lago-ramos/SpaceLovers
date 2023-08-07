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

    // Methode a appeler dans game.cpp pour créer les buttons
    void createButtons();
};

#endif
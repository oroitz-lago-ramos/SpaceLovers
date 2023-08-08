#include "player.hpp"
#include "graphics.hpp"


Player::Player()
    //Pour changer la couleur on modifie les trois premiers paramètres
    : Character(200, 200, 200, Graphics::screenWidth / 2, Graphics::screenHeight - 40, 50, 50 , 10.0f)
{
}

Player::~Player()
{
}

void Player::update(int direction)
{
    if (direction == -1)
    {
        this->moveLeft();
    }
    else
    {
        this->moveRight();
    }
}
#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>

#include "entity.hpp"
#include "graphics.hpp"
#include "inGameItem.hpp"
#include "level.hpp"
#include "player.hpp"

InGameItem::InGameItem()
    : Character(30, 200, 20, rand()%Graphics::screenWidth, 10, 10, 10, 0.02f, 1)
{
    Level::powerUps.insert(this);
}

InGameItem::~InGameItem()
{
    Level::powerUps.erase(this);
}

void InGameItem::update()
{
    this->checkCollisions();
    this -> moveDown();
    if (this -> rect.y > Graphics::screenHeight)
    {
        this -> ~InGameItem();
    }
}

void InGameItem::checkCollisions()
{
    if(SDL_HasIntersection(&this->rect, &Player::instance->rect))
    {
        this->heal();
        this->~InGameItem();
    }
}

void InGameItem::heal()
{   
    
    /* int heal = 20;
    //Comment faire que ça heal max jusqu'a maxLifePoints
    if (Player::instance->lifePoints < Player::instance->maxLifePoints - heal)
    {
        Player::instance->lifePoints += 20;
    } */

    //Sinon :
        Player::instance-> lifePoints = std::min(Player::instance->lifePoints += 20, Player::instance->maxLifePoints);
    
}

void InGameItem::speedUp()
{
    /* Comment faire les 10 secondes?
    this-> itemTimer = 0;
    float tempSpeed = Player::instance->speed;
    while(itemTimer < Xvaleur)
    {
        Player::instance->speed += 0.1;
    }
    */
}

void InGameItem::changeNumberOfProjectiles(int number)
{
    Player::instance->numberOfProjectiles = number;
}
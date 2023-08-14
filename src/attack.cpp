#include <SDL2/SDL.h>

#include "attack.hpp"
#include "enemy.hpp"
#include "graphics.hpp"

Attack::Attack(Enemy *enemy, int type)
    : enemy(enemy), type(type)
{
    if (type == 0)
    {
        this->timeSinceLastAttack = 0;
        this->timeSinceAttackStart = 0;
        this->attackDuration = 1000000000;
        this->attackCooldown = 3000000000;
        this->multiplier = 1;
    }
}

Attack::~Attack()
{
}

Attack::laser()
{
    Rect *laser = new Rect(255, 0, 0, this->enemy->getX(), 
        (Graphics::screenHeight - this->enemy->getY()) / 2 + this->enemy->getY(), 
        this->enemy->width/2, Graphics::screenHeight - this->enemy->getY());
    if(SDL_HasIntersection(&laser->rect, &Player::instance->rect))
    {
        Player::instance->takeDamage(this->enemy->power * this->multiplier);
    }
    laser->render();
}

Attack::sweep()
{
}

Attack::update()
{
    this->timeSinceLastAttack += Game::frameTime;
    if (this->timeSinceLastAttack >= this->attackCooldown)
    {
        this->timeSinceAttackStart += Game::frameTime;
        if (this->timeSinceAttackStart >= this->attackDuration)
        {
            this->timeSinceLastAttack = 0;
            this->timeSinceAttackStart = 0;
        }
        if (this->type == 0)
        {
            this->laser();
        }
        if (this->type == 1)
        {
            this->sweep();
        }
    }
}
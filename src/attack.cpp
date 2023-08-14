#include <SDL2/SDL.h>

#include "attack.hpp"
#include "enemy.hpp"
#include "graphics.hpp"
#include "rect.hpp"
#include "player.hpp"
#include "game.hpp"
#include "projectile.hpp"

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
    if (type == 1)
    {
        this->timeSinceLastAttack = 0;
        this->timeSinceAttackStart = 0;
        this->attackDuration = 2000000000;
        this->attackCooldown = 2000000000;
        this->multiplier = 0.3;
    }
}

Attack::~Attack()
{
}

void Attack::laser()
{
    Rect *laser = new Rect(255, 0, 0, this->enemy->getX(),
                           (Graphics::screenHeight - this->enemy->getY()) / 2 + this->enemy->getY(),
                           this->enemy->getWidth() / 2, Graphics::screenHeight - this->enemy->getY());
    if (SDL_HasIntersection(&laser->rect, &Player::instance->rect))
    {
        Player::instance->takeDamage(this->enemy->power * this->multiplier);
    }
    laser->render(true);
}

void Attack::sweep()
{
    static long long unsigned int time = 0;
    static float sweepRadius = 1;
    time += Game::frameTime;
    if (time > 100000000)
    {
        sweepRadius -= 0.1;
        if (sweepRadius <= -1)
        {
            sweepRadius = 1;
        }
        new Projectile(0, 255, 0, this->enemy->getX(),
                       this->enemy->getY() + this->enemy->getHeight(), this->enemy->power * this->multiplier, 0.05f,
                       sweepRadius, 1);
        time = 0;
    }
}

void Attack::update()
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
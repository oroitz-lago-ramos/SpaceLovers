#ifndef ATTACK_HPP
#define ATTACK_HPP

#include "enemy.hpp"

class Attack
{
public:
    Attack(Enemy *enemy, int type);
    ~Attack();

    long long unsigned int timeSinceLastAttack;
	long long unsigned int timeSinceAttackStart;
	long long unsigned int attackDuration;
	long long unsigned int attackCooldown;
	float multiplier;
    Enemy *enemy;
    int type;

    void laser();
    void sweep();
    void update();

};

#endif
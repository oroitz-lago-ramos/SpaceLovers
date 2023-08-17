#ifndef PLAYERBOOST_HPP
#define PLAYERBOOST_HPP

#include <iostream>
#include <functional>

class PlayerBoost
{
public:
    PlayerBoost(long long unsigned int powerUpDuration, long long unsigned int timeSincePowerUpStart, std::function<void()> onEnd, int powerUp);
    ~PlayerBoost();

    long long unsigned int powerUpDuration;
    long long unsigned int timeSincePowerUpStart;

    std::function<void()> onEnd;
    int powerUp;
    long long unsigned int boostLeft;

    bool update();
};

#endif
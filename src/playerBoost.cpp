#include "playerBoost.hpp"
#include "game.hpp"

PlayerBoost::PlayerBoost(long long unsigned int powerUpDuration, long long unsigned int timeSincePowerUpStart, std::function<void()> onEnd)
    : powerUpDuration(powerUpDuration), timeSincePowerUpStart(timeSincePowerUpStart), onEnd(onEnd)
{
}

PlayerBoost::~PlayerBoost()
{
}

bool PlayerBoost::update()
{
    this->timeSincePowerUpStart += Game::frameTime;
    if (this->timeSincePowerUpStart >= this->powerUpDuration)
    {
        this->onEnd();
        return false;
    }
    return true;
}
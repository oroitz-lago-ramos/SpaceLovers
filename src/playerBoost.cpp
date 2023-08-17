#include "playerBoost.hpp"
#include "game.hpp"

PlayerBoost::PlayerBoost(long long unsigned int powerUpDuration, long long unsigned int timeSincePowerUpStart, std::function<void()> onEnd, int powerUp)
    : powerUpDuration(powerUpDuration), timeSincePowerUpStart(timeSincePowerUpStart), onEnd(onEnd), powerUp(powerUp)
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
#include "player.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "projectile.hpp"

Player *Player::instance = nullptr;

Player::Player()
	// Pour changer la couleur on modifie les trois premiers paramètres
	: Character(200, 200, 200, Graphics::screenWidth / 2 - 20, Graphics::screenHeight - 30, 40, 40, 0.05f)
{
	Player::instance = this;
	this->lifePoints = 100.0f;
}

Player::~Player()
{
}

void Player::update()
{
	if (Game::inputs & BUTTON_LEFT && this->getX() > 0 + this->width / 2)
	{
		this->moveLeft();
	}
	else if (Game::inputs & BUTTON_RIGHT && this->getX() < Graphics::screenWidth - this->width / 2)
	{
		this->moveRight();
	}
	if (Game::inputs & BUTTON_SHOOT)
	{
		this->shoot();
	}
}

void Player::shoot()
{
	new Projectile(0, 255, 0, this->getX(), this->getY() - this->height/2, -1);
}


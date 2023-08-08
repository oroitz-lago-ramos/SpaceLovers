#include "player.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "projectile.hpp"

Player *Player::instance = nullptr;

Player::Player()
	// Pour changer la couleur on modifie les trois premiers paramètres
	: Character(200, 200, 200, Graphics::screenWidth / 2 - 25, Graphics::screenHeight - 70, 50, 50, 0.01f)
{
	Player::instance = this;
}

Player::~Player()
{
}

void Player::update(int direction)
{
	if (Game::inputs & BUTTON_LEFT)
	{
		this->moveLeft();
	}
	else if (Game::inputs & BUTTON_RIGHT)
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
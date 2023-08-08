#include <SDL2/SDL.h>
#include "character.hpp"
#include "projectile.hpp"
#include "level.hpp"

Projectile::Projectile(int r, int g, int b, SDL_Rect rect)
	: Character(r, g, b, rect, 1.0f)
{
	Level::projectiles.insert(this);
}

Projectile::~Projectile()
{
	Level::projectiles.erase(this);
}
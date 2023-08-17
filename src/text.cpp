#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "text.hpp"
#include "graphics.hpp"
#include "entity.hpp"

Text::Text()
	: Entity(0, 0, 0, 0, 0, 0, 0)
{
}

Text::Text(int r, int g, int b, int x, int y, int width, int height, const char *message, TTF_Font *font)
	: Entity(30, 30, 30, x, y, width, height),
	  color({(Uint8)r, (Uint8)g, (Uint8)b, 255}), fontChoice(font)
{
	this->message = strdup(message);
	SDL_Surface *text = TTF_RenderText_Blended(this->fontChoice, this->message, this->color);
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, text);
	SDL_FreeSurface(text);
}

Text::~Text()
{
	free(this->message);
}

void Text::textUpdate(const char *message)
{
	if (strcmp(this->message, message) == 0)
	{
		return;
	}
	free(this->message);
	this->message = strdup(message);
	SDL_DestroyTexture(this->texture);
	SDL_Surface *text = TTF_RenderText_Blended(this->fontChoice, this->message, this->color);
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, text);
	SDL_FreeSurface(text);
}
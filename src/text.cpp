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

Text::Text(int r, int g, int b, int x, int y, int width, int height, const char *message, const char *font, int fontSize)
	: Entity(30, 30, 30, x, y, width, height),
	  message(message), font(font)
{
	this->fontChoice = TTF_OpenFont(font, fontSize);
	SDL_Surface *text = TTF_RenderText_Blended(this->fontChoice, this->message, {0, 250, 200, 255});
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, text);
	SDL_FreeSurface(text);
}

Text::~Text()
{
	TTF_CloseFont(this->fontChoice);
}

void Text::textUpdate(const char *message)
{
	// if (this->message != message)
	// {
	this->message = message;
	SDL_DestroyTexture(this->texture);
	SDL_Surface *text = TTF_RenderText_Blended(this->fontChoice, this->message, (SDL_Color){255, 255, 255, 255});
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, text);
	SDL_FreeSurface(text);
	// }
}
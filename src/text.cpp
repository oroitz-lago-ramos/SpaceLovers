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
	SDL_Surface *text = TTF_RenderText_Blended_Wrapped(this->fontChoice, this->message, this->color, this->getWidth());
	// this->createMultiLineText();
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
	this->texture = nullptr;
	// this->createMultiLineText();
	SDL_Surface *text = TTF_RenderText_Blended_Wrapped(this->fontChoice, this->message, this->color, this->getWidth());
	this->texture = SDL_CreateTextureFromSurface(Graphics::renderer, text);
	SDL_FreeSurface(text);
}

void Text::createMultiLineText()
{
	char *message = strdup(this->message);
	int lines = 1;
	for (long long unsigned int i = 0; i < strlen(message); i++)
	{
		if (message[i] == '\n')
		{
			lines++;
		}
	}

	char **messages = (char **)malloc(sizeof(char *) * lines);
	for (int i = 0; i < lines; i++)
	{
		messages[i] = (char *)malloc(sizeof(char) * 100);
	}

	int j = 0;
	int k = 0;
	for (long long unsigned int i = 0; i < strlen(message); i++)
	{
		if (message[i] == '\n')
		{
			messages[j][k] = '\0';
			j++;
			k = 0;
		}
		else
		{
			messages[j][k] = message[i];
			k++;
		}
	}
	messages[j][k] = '\0';

	SDL_DestroyTexture(this->texture);
	SDL_Texture *texture = SDL_CreateTexture(Graphics::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->getWidth(), this->getHeight());
	SDL_SetRenderTarget(Graphics::renderer, texture);
	SDL_SetRenderDrawColor(Graphics::renderer, 30, 30, 30, 0);
	SDL_RenderClear(Graphics::renderer);
	SDL_SetRenderDrawColor(Graphics::renderer, this->getR(), this->getG(), this->getB(), 255);
	// SDL_Rect rect = {0, 0, this->getWidth(), this->getHeight()};

	int lineHeight = this->getHeight() / lines;
	int startY = 0;
	// int startY = this->getY() - (this->getHeight() / 2) + (lineHeight / 2);
	for (int i = 0; i < lines; i++)
	{
		SDL_SetRenderTarget(Graphics::renderer, texture);
		SDL_SetRenderTarget(Graphics::renderer, texture);
		SDL_Surface *text = TTF_RenderText_Blended(this->fontChoice, messages[i], this->color);
		SDL_Rect line = {(int)this->getX(), startY + lineHeight * i, this->getWidth(), lineHeight};
		SDL_Texture *lineTexture = SDL_CreateTextureFromSurface(Graphics::renderer, text);
		SDL_RenderCopy(Graphics::renderer, lineTexture, NULL, &line);
		SDL_DestroyTexture(lineTexture);
		SDL_FreeSurface(text);
		SDL_SetRenderTarget(Graphics::renderer, NULL);
		SDL_RenderCopy(Graphics::renderer, texture, NULL, &line);
	}
	// for (int i = 0; i < lines; i++)
	// {
	// 	std::cout << messages[i] << std::endl;
	// }
	SDL_SetRenderTarget(Graphics::renderer, NULL);
	this->texture = texture;
	free(message);
	for (int i = 0; i < lines; i++)
	{
		free(messages[i]);
	}
	free(messages);
}
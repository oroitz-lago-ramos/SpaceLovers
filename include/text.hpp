#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "entity.hpp"

class Text : public Entity
{
public:
	Text();
	Text(int r, int g, int b, int x, int y, int width, int height, const char *message, TTF_Font *font);
	~Text();

	char *message;
	SDL_Color color;
	TTF_Font *fontChoice;

	void textUpdate(const char *message);
	void createMultiLineText();
};

#endif
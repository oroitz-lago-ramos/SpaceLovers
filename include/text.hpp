#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "entity.hpp"

class Text:public Entity
{
public:
    Text();
    Text(int r, int g, int b, int x, int y, int width, int height, const char* message, const char* font, int fontSize);
    ~Text();

    TTF_Font *fontChoice;
    const char* message;
    const char* font;
    int fontSize;
	SDL_Color color;

    void textUpdate(const char *message);
};

#endif
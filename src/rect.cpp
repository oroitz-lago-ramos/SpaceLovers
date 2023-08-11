#include <iostream>
#include <SDL2/SDL.h>

#include "rect.hpp"
#include "graphics.hpp"
#include "entity.hpp"

Rect::Rect(int r, int g, int b, int x, int y, int width, int height)
    : Entity(r, g, b, x, y, width, height)
{
}
void Rect::render(bool fill)
{
    SDL_SetRenderDrawColor(Graphics::renderer, this->r, this->g, this->b, 255);
    if (fill)
    {
        SDL_RenderFillRect(Graphics::renderer, &rect);
    }
    else
    {
        SDL_RenderDrawRect(Graphics::renderer, &rect);
    }
}

Rect::~Rect()
{
}

#include <iostream>
#include <SDL2/SDL.h>

#include "rect.hpp"
#include "graphics.hpp"
#include "entity.hpp"

Rect::Rect()
{
}

Rect::Rect(int r, int g, int b, int x, int y, int width, int height)
    : Entity(r, g, b, x, y, width, height)
{
    this->rect = {this->x, this->y, this->width, this->height};
    SDL_SetRenderDrawColor(Graphics::renderer, this->r, this->g, this->b, 255);
    SDL_RenderDrawRect(Graphics::renderer, &rect);
}

Rect::RectFill(int r, int g, int b, int x, int y, int width, int height)
    : Entity(r, g, b, x, y, width, height)
{
    this->rect = {this->x, this->y, this->width, this->height};
    SDL_SetRenderDrawColor(Graphics::renderer, this->r, this->g, this->b, 255);
    SDL_RenderFillRect(Graphics::renderer, &rect);
}

Rect::~Rect()
{
}

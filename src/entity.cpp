#include <iostream>
#include "functional"
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "graphics.hpp"

Entity::Entity(int r, int g, int b, int x, int y, int width, int height)
   :r(r), g(g), b(b), x(x), y(y), width(width), height(height), rect({x - width / 2, y - height / 2, width, height}),
   texture(nullptr)
{
}

Entity::~Entity()
{
    SDL_DestroyTexture(this -> texture);
}

void Entity::render()
{
    SDL_SetRenderDrawColor(Graphics::renderer, this->r, this->g, this->b, 255);
    SDL_RenderFillRect(Graphics::renderer, &this->rect);
    if (this -> texture)
    {
        SDL_RenderCopy(Graphics::renderer, this -> texture, NULL, &this -> rect);
    }
}

void Entity::setX(float x)
{
    this -> x = x;
    this -> rect.x = (int)x - this -> width / 2;
}

float Entity::getX()
{
    return this -> x;
}

void Entity::setY(float y)
{
    this -> y = y;
    this -> rect.y = (int)y - this -> height / 2;
}

float Entity::getY()
{
    return this -> y;
}
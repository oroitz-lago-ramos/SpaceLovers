#include <iostream>
#include "functional"
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "graphics.hpp"

Entity::Entity(int r, int g, int b, SDL_Rect rect)
   :r(r), g(g), b(b), rect(rect)
{}

Entity::~Entity()
{}

void Entity::render()
{
    SDL_SetRenderDrawColor(Graphics::renderer, this->r, this->g, this->b, 255);
    SDL_RenderFillRect(Graphics::renderer, &this->rect);
}
#include <iostream>
#include "functional"
#include <SDL2/SDL.h>

#include "button.hpp"
#include "graphics.hpp"

Button::Button()
{
    std::cout << "Button constructor called!" << std::endl;
}

Button::Button(int r, int g, int b, SDL_Rect rect, std::function<void()> onClick)
    : r(r), g(g), b(b), rect(rect), onClick(onClick)
{
    std::cout << "Button constructor called!" << std::endl;
}

Button::~Button()
{
    std::cout << "Button destructor called!" << std::endl;
}

void Button::render()
{
    SDL_SetRenderDrawColor(Graphics::renderer, this->r, this->g, this->b, 255);
    SDL_RenderFillRect(Graphics::renderer, &this->rect);
}
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
    // Permet d'ajouter un nouveau bouton à la liste
    Graphics::buttons.insert(this);
    
    std::cout << "Button constructor called!" << std::endl;
}

Button::~Button()
{
    // Permet de supprimer un bouton de la liste
    Graphics::buttons.erase(this);

    std::cout << "Button destructor called!" << std::endl;
}

void Button::render()
{
    SDL_SetRenderDrawColor(Graphics::renderer, this->r, this->g, this->b, 255);
    SDL_RenderFillRect(Graphics::renderer, &this->rect);
}
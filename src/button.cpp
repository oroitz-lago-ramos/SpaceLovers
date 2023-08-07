#include <iostream>
#include <SDL2/SDL.h>

#include "button.hpp"
#include "graphics.hpp"
#include "entity.hpp"

Button::Button(int r, int g, int b, SDL_Rect rect, std::function<void()> onClick)
    : Entity(r, g, b, rect),
    onClick(onClick)
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
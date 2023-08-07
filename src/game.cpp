#include <iostream>

#include <SDL2/SDL.h>
#include "button.hpp"
#include "graphics.hpp"
#include "game.hpp"

Game::Game()
{
    // Appel de la méthode de création des boutons
    this -> createButtons();

    std::cout << "Game destructor called!" << std::endl;
    
    while (true)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                const SDL_Point point = {event.button.x, event.button.y};

                // Test tous les boutons du tableau pour voir si il est sur le SDL_Point
                for (auto button : std::set<Button *>(Graphics::buttons))
                {
                    if(SDL_PointInRect(&point, &button->rect))
                    {
                        button->onClick();
                        break;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(Graphics::renderer, 30, 30, 30, 30);
        SDL_RenderClear(Graphics::renderer);

        SDL_SetRenderDrawColor(Graphics::renderer, 255, 255, 255, 255);
        SDL_Rect rectangle = {50, 10, 100, 100};
        SDL_RenderFillRect(Graphics::renderer, &rectangle);

        // Créer le rendu graphics de chaque bouton
        for (auto button : std::set<Button *>(Graphics::buttons))
        {
            button->render();
        }

        SDL_RenderPresent(Graphics::renderer);
    }
}

Game::~Game()
{
    std::cout << "Game destructor called!" << std::endl;
}

// Methode pour créer des buttons, chaque nouveau bouton doit être fais dans la méthode

void Game::createButtons()
{
    new Button(255, 0, 0, {50, 50, 100, 100}, []() 
                    { std::cout << "Button1 clicked!" << std::endl;});
    new Button(0, 255, 0, {200, 50, 100, 100}, []() 
                    { std::cout << "Button2 clicked!" << std::endl;});
    new Button(0, 0, 255, {400, 400, 100, 100}, []() 
                    { std::cout << "Button3 clicked!" << std::endl;}); 
}
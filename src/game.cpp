#include <iostream>

#include <SDL2/SDL.h>
#include "button.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "enemy.hpp"

Game::Game()
{
    // Appel de la méthode de création des boutons
    this -> createButtons();
    this -> createEnemys();

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

                // Test tous les boutons du tableau pour voir si le &point est dans un &button->rect
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

        // Créer le rendu graphique de chaque bouton
        for (auto button : std::set<Button *>(Graphics::buttons))
        {
            button->render();
        }
        for (auto enemy : std::set<Enemy *>(Graphics::enemys))
        {
            enemy->render();
        }

        SDL_RenderPresent(Graphics::renderer);
    }
}

Game::~Game()
{
    std::cout << "Game destructor called!" << std::endl;
}

//Methode pour créer des boutons, chaque nouveau bouton doit être fait dans la méthode

void Game::createButtons()
{
    new Button(255, 0, 0, {50, 50, 100, 100}, []() 
                    { std::cout << "Button1 clicked!" << std::endl;});
    new Button(0, 255, 0, {200, 50, 100, 100}, []() 
                    { std::cout << "Button2 clicked!" << std::endl;});
    new Button(0, 0, 255, {400, 400, 100, 100}, []() 
                    { std::cout << "Button3 clicked!" << std::endl;});
}

//Methode pour créer des ennemi, chaque nouvel ennemi doit être fait dans la méthode

void Game::createEnemys()
{
    new Enemy(135, 53, 77, {20, 20, 40, 40});
    new Enemy(53, 135, 77, {150, 20, 40, 40});
    new Enemy(77, 53, 135, {350, 20, 40, 40});
}
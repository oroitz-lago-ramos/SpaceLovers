#include <iostream>

#include <SDL2/SDL.h>
#include "button.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "enemy.hpp"
#include "level.hpp"
#include "projectile.hpp"

Game::Game()
{
    // Appel de la méthode de création des boutons
    this -> createButtons();
    srand(time(NULL));
    Level level;

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
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.scancode == SDL_SCANCODE_A)
                {
                    player.update(-1);
                }
                else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.scancode == SDL_SCANCODE_D)
                {
                    player.update(1);
                }
                else if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP || event.key.keysym.scancode == SDL_SCANCODE_W)
                {
                    new Projectile(0, 255, 0, this->player.getX(), this -> player.getY(), -1);
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
        
        for (auto enemy : std::set<Enemy *>(Level::enemies))
        {
            enemy->update();
            enemy->render();
        }

        for (auto projectile : std::set<Projectile *>(Level::projectiles))
        {
            projectile->update();
            projectile->render();
        }

        level.update();

        // Affichage du joueur
        player.render();


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
}
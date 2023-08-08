#include <iostream>

#include <SDL2/SDL.h>
#include "button.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include "enemy.hpp"
#include "level.hpp"
#include "projectile.hpp"

int Game::inputs = 0;

Game::Game()
{
    // Appel de la méthode de création des boutons
    this->createButtons();
    srand(time(NULL));
    Level level;

    std::cout << "Game destructor called!" << std::endl;

    while (true)
    {
        this->eventLoop();

        SDL_SetRenderDrawColor(Graphics::renderer, 30, 30, 30, 30);
        SDL_RenderClear(Graphics::renderer);

        this -> renderLoop();

        level.update();

        // Affichage du joueur
		this->player.update(1);
        this -> player.render();

        SDL_RenderPresent(Graphics::renderer);
    }
}

Game::~Game()
{
    std::cout << "Game destructor called!" << std::endl;
}

// Methode pour créer des boutons, chaque nouveau bouton doit être fait dans la méthode

void Game::createButtons()
{
}

void Game::eventLoop()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            exit(0);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            this->mousebuttondown(&event);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            this->keydown(&event);
        }
		else if (event.type == SDL_KEYUP)
		{
			this->keyup(&event);
		}
    }
}

void Game::mousebuttondown(SDL_Event *event)
{
    const SDL_Point point = {event->button.x, event->button.y};

    // Test tous les boutons du tableau pour voir si le &point est dans un &button->rect
    for (auto button : std::set<Button *>(Graphics::buttons))
    {
        if (SDL_PointInRect(&point, &button->rect))
        {
            button->onClick();
            break;
        }
    }
}

void Game::keydown(SDL_Event *event)
{
    if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.scancode == SDL_SCANCODE_A)
    {
		Game::inputs |= BUTTON_LEFT;
        // player.update(-1);
    }
    else if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.scancode == SDL_SCANCODE_D)
    {
		Game::inputs |= BUTTON_RIGHT;
        // player.update(1);
    }
    else if (event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_UP || event->key.keysym.scancode == SDL_SCANCODE_W)
    {
		Game::inputs |= BUTTON_SHOOT;
        // new Projectile(0, 255, 0, this->player.getX(), this->player.getY(), -1);
    }
}

void Game::keyup(SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.scancode == SDL_SCANCODE_A)
    {
		Game::inputs &= ~BUTTON_LEFT;
        // player.update(-1);
    }
    else if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.scancode == SDL_SCANCODE_D)
    {
		Game::inputs &= ~BUTTON_RIGHT;
        // player.update(1);
    }
    else if (event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_UP || event->key.keysym.scancode == SDL_SCANCODE_W)
    {
		Game::inputs &= ~BUTTON_SHOOT;
        // new Projectile(0, 255, 0, this->player.getX(), this->player.getY(), -1);
    }
}

void Game::renderLoop()
{
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
}
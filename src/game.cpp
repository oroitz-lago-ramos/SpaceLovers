#include <iostream>
#include "game.hpp"
#include "graphics.hpp"
#include <SDL2/SDL.h>

Game::Game()
{
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
        }
        SDL_SetRenderDrawColor(this->graphics.renderer, 30, 30, 30, 30);
        SDL_RenderClear(this->graphics.renderer);

        SDL_SetRenderDrawColor(this->graphics.renderer, 255, 255, 255, 255);
        SDL_Rect rectangle = {50, 10, 100, 100};
        SDL_RenderFillRect(this->graphics.renderer, &rectangle);
        SDL_RenderPresent(this->graphics.renderer);
    }
}

Game::~Game()
{
    std::cout << "Game destructor called!" << std::endl;
}
#include <iostream>

#include <SDL2/SDL.h>
#include "button.hpp"
#include "graphics.hpp"
#include "game.hpp"

Game::Game()
{
    std::cout << "Game destructor called!" << std::endl;
    Button button = Button(255, 0, 0, {50, 50, 100, 100}, []() 
                            { std::cout << "Button clicked!" << std::endl;});
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
                if(SDL_PointInRect(&point, &button.rect))
                    button.onClick();
            }
        }
        SDL_SetRenderDrawColor(Graphics::renderer, 30, 30, 30, 30);
        SDL_RenderClear(Graphics::renderer);

        SDL_SetRenderDrawColor(Graphics::renderer, 255, 255, 255, 255);
        SDL_Rect rectangle = {50, 10, 100, 100};
        SDL_RenderFillRect(Graphics::renderer, &rectangle);

        button.render();

        SDL_RenderPresent(Graphics::renderer);
    }
}

Game::~Game()
{
    std::cout << "Game destructor called!" << std::endl;
}
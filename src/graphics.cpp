#include <iostream>
#include "graphics.hpp"
#include <SDL2/SDL.h>

Graphics::Graphics()
{
    std::cout << "Game destructor called!" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    this->window = SDL_CreateWindow("C++",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
}

Graphics::~Graphics()
{
    std::cout << "Game destructor called!" << std::endl;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
#include <iostream>
#include "graphics.hpp"
#include <SDL2/SDL.h>

SDL_Window *Graphics::window = nullptr;
SDL_Renderer *Graphics::renderer = nullptr;


//Initialisation d'un tableau de bouton à 0
std::set<Button *> Graphics::buttons = {};

Graphics::Graphics()
{
    std::cout << "Game destructor called!" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    Graphics::window = SDL_CreateWindow("C++",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    Graphics::renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
}

Graphics::~Graphics()
{
    std::cout << "Game destructor called!" << std::endl;
    SDL_DestroyRenderer(Graphics::renderer);
    SDL_DestroyWindow(Graphics::window);
    SDL_Quit();
}
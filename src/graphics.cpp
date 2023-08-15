#include <iostream>
#include "graphics.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int Graphics::windowWidth = 1000;
int Graphics::screenWidth = 800;
int Graphics::screenHeight = 600;

SDL_Window *Graphics::window = nullptr;
SDL_Renderer *Graphics::renderer = nullptr;

// Initialisation d'un tableau de bouton à 0
std::set<Button *> Graphics::buttons = {};

Graphics::Graphics()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Graphics::window = SDL_CreateWindow("C++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->screenHeight, SDL_WINDOW_SHOWN);
	Graphics::renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();
	SDL_SetRenderDrawBlendMode(Graphics::renderer, SDL_BLENDMODE_BLEND);
}

Graphics::~Graphics()
{
	for (auto button : std::set<Button *>(Graphics::buttons))
	{
		button->~Button();
	}
	SDL_DestroyRenderer(Graphics::renderer);
	SDL_DestroyWindow(Graphics::window);
	TTF_Quit();
	SDL_Quit();
}
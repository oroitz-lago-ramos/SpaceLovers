#include <iostream>
#include "graphics.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int Graphics::windowWidth = 1000;
int Graphics::screenWidth = 800;
int Graphics::screenHeight = 600;

SDL_Window *Graphics::window = nullptr;
SDL_Renderer *Graphics::renderer = nullptr;
SDL_Texture *Graphics::textures[] = {};
SDL_Texture *Graphics::backgrounds[] = {};
// Initialisation d'un tableau de bouton à 0
std::set<Button *> Graphics::buttons = {};

Graphics::Graphics()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Graphics::window = SDL_CreateWindow("C++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->screenHeight, SDL_WINDOW_SHOWN);
	Graphics::renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDL_SetRenderDrawBlendMode(Graphics::renderer, SDL_BLENDMODE_BLEND);
	SDL_Surface *enemy = IMG_Load("assets/ennemies.png");
	Graphics::textures[ENEMYTEXTURE1] = SDL_CreateTextureFromSurface(Graphics::renderer, enemy);
	SDL_FreeSurface(enemy);
	SDL_Surface *boss = IMG_Load("assets/boss.png");
	Graphics::textures[ENEMYTEXTURE2] = SDL_CreateTextureFromSurface(Graphics::renderer, boss);
	SDL_FreeSurface(boss);
	SDL_Surface *player = IMG_Load("assets/player.png");
	Graphics::textures[PLAYER] = SDL_CreateTextureFromSurface(Graphics::renderer, player);
	SDL_FreeSurface(player);
	SDL_Surface *laserBeam = IMG_Load("assets/laser.png");
	Graphics::textures[LASER] = SDL_CreateTextureFromSurface(Graphics::renderer, laserBeam);
	SDL_FreeSurface(laserBeam);
	SDL_Surface *projectile = IMG_Load("assets/flame1.png");
	Graphics::textures[PROJECTILE] = SDL_CreateTextureFromSurface(Graphics::renderer, projectile);
	SDL_FreeSurface(projectile);
	for (int i = 0; i < 10; i++)
	{
		char str[30];
		snprintf(str, 30, "assets/space/spaceLevel%d.gif", i + 1);
		SDL_Surface *spaceLevel1 = IMG_Load(str);
		Graphics::backgrounds[i] = SDL_CreateTextureFromSurface(Graphics::renderer, spaceLevel1);
		SDL_FreeSurface(spaceLevel1);
	}
}

Graphics::~Graphics()
{
	for (auto button : std::set<Button *>(Graphics::buttons))
	{
		button->~Button();
	}
	for (int i = 0; i < 5; i++)
	{
		SDL_DestroyTexture(Graphics::textures[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		SDL_DestroyTexture(Graphics::backgrounds[i]);
	}
	SDL_DestroyRenderer(Graphics::renderer);
	SDL_DestroyWindow(Graphics::window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
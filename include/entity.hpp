#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2/SDL.h>

class Entity
{
public:
    Entity(int r, int g, int b, SDL_Rect rect);
    ~Entity();
    void render();

    int r;
    int g;
    int b;
    SDL_Rect rect;
};

#endif
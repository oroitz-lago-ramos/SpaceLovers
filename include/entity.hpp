#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2/SDL.h>

class Entity
{
public:
    Entity(int r, int g, int b, int x, int y, int width, int height);
    ~Entity();
    void render();
    void setX(float x);
    float getX();
    void setY(float y);
    float getY();

    int r;
    int g;
    int b;
    int width;
    int height;
    SDL_Rect rect;

private:
    float x;
    float y;

};

#endif
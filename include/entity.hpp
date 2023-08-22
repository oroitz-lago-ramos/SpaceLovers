#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2/SDL.h>

class Entity
{
private:
	int r;
	int g;
	int b;
	float x;
	float y;
	int width;
	int height;

public:
	Entity(int r, int g, int b, int x, int y, int width, int height);
	Entity(int r, int g, int b, int x, int y, int width, int height, bool drawRect);
	~Entity();
	void render();
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();
	void setWidth(int width);
	int getWidth();
	void setHeight(int height);
	int getHeight();
	void setR(int r);
	int getR();
	void setG(int g);
	int getG();
	void setB(int b);
	int getB();

	SDL_Rect rect;
	SDL_Texture *texture;
	bool destroyTexture;
	bool drawRect;
};

#endif
#pragma once
#include "Game.h"

class GameObject {

public:
	GameObject(const char* spritesheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:

	int xpos;
	int ypos;


	SDL_Texture* objectTexture; //SDL function we use to create our player texture
	SDL_Rect srcRect, destRect; //Creating our rectangles for our rendercopy function in gameobject cpp
	SDL_Event event;

	bool isRunning = true;
};
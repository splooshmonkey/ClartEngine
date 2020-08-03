#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game { //Our game class which is used in the game.cpp and called in the main

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	//functions for our game loop
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();


	static SDL_Renderer* renderer;

private:
	int count = 0;
	bool isRunning;
	SDL_Window* window;

};
#pragma once
#include "Game.h"

class Map //A class for our game map
{
public:


	Map();
	~Map();

	void LoadMap(int arr[20][25]); //function to load the map
	void CreateMap(); //function to create the map

private:

	SDL_Rect src, dest; //holds our map source and destination for rendering

	SDL_Texture* mud;
	SDL_Texture* water;
	SDL_Texture* grass;


	int map[20][25];

};
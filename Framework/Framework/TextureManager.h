#pragma once

#include "Game.h"


class TextureManager {


public:
	static SDL_Texture* LoadTexture(const char* fileName); //SDL function to create our texture, takes in the file we want to use
	static void Create(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};

#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) //our SDL function from the header
{
	SDL_Surface* tempSurface = IMG_Load(texture); //Here we create a temporary surface for our player texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface); //Using the png
	SDL_FreeSurface(tempSurface); //We clean it up after we are done

	return tex;
}

void TextureManager::Create(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) 
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

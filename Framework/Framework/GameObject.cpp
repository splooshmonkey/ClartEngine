#include "GameObject.h"
#include "TextureManager.h"
GameObject::GameObject(const char* spritesheet, int x, int y)
{
	objectTexture = TextureManager::LoadTexture(spritesheet);

	xpos = x; //Position of
	ypos = y; //our object
}

void GameObject::Update()

{
	/*
	xpos = xpos++ this was a test to move my characters diagonally
	ypos = ypos++
	*/


	srcRect.h = 32; //Height and width of our rectangles aka our character
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2; //multiplied by two as my character was too small
	destRect.h = srcRect.h * 2;


	//while (isRunning)				Was going to use a loop for movement while the game is running, but it ended up getting stuck here and not reaching the renderer until SDL_Quit was triggered
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
			else if (event.type == SDL_KEYDOWN)			//This code kind of works, however it stops my window from closing when you hit the X
			{											//I tried to find a better fix but couldn't. Will come back if I have more time
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					ypos += -5;
					break;
				case SDLK_DOWN:
					ypos += 5;
					break;
				case SDLK_LEFT:
					xpos += -5;
					break;
				case SDLK_RIGHT:
					xpos += 5;
					break;
				case SDLK_ESCAPE:
					isRunning = false;
					break;
				}
			}
		}
	}
}


void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect); //adds our texture to the renderer


}

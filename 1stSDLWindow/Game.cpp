#include "Game.h"
#include "GameObject.h"
#include "Map.h"

GameObject* player;
GameObject* enemy;
Map* map;
SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) //Here we create the variables we want for our game window, which can then be set in our main.cpp
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN; //SDL function for fullscreen
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //initialises our subsystems to get the game up and running
	{
		std::cout << "Subsytems Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags); //SDL function to create our game window
			if (window)
			{
				std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0); //SDL function to create our renderer
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Once the renderer has been created we use another SDL function to set the colour
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}

	player = new GameObject("Textures/Character.png", 0, 0);
	enemy = new GameObject("Textures/Enemy.png", 200, 0);
	map = new Map();
}

void Game::handleEvents() //Event handling function
{

	SDL_Event event; //Creates the event structure
	SDL_PollEvent(&event); //removes the next event from the queue. If there are no events on the queue it returns 0, otherwise it returns 1
	switch (event.type) //We use a switch statement to handle each event type seperately
	{
	case SDL_QUIT:
		isRunning = false;
	default:
		break;
	}

}

void Game::update() //Update function
{
	player->Update();
	enemy->Update();
}

void Game::render()
{
	SDL_RenderClear(renderer); //Clears the screen to our selected colour
	map->CreateMap(); //places our map on the screen
	player->Render(); //places our player on the screen
	enemy->Render(); //places an enemy on the screen
	SDL_RenderPresent(renderer); //Actually makes our colour show up on the renderer
}

void Game::clean() //Game clean function
{
	SDL_DestroyWindow(window); //SDL function to destroy the window we created
	SDL_DestroyRenderer(renderer); //SDL function to destroy the renderer we created
	SDL_Quit(); //Cleans up all our subsystems we initialised
	std::cout << "Game cleaned" << std::endl;
}
#include "Game.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <LuaBridge\LuaBridge.h>

Game* game = nullptr;

int main(int argc, char* argv[])
{

	//const int FPS = 60;
	//const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	using namespace luabridge;


	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef t = getGlobal(F, "window");
	LuaRef title = t["title"];
	LuaRef w = t["width"];
	LuaRef h = t["height"];

	std::string titleString = title.cast<std::string>();
	int width = w.cast<int>();
	int height = h.cast<int>();

	game->init("ClartEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false); //Initialises the engine and sets parameters for the window

	while (game->running()) //The game order
	{	

		frameStart = SDL_GetTicks();  //Sets frame start to how many seconds its been since we initialised SDL

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		/*if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime); //Delays our frames		delaying my frames made my input really bad, so I have commented it out for now
		}
		*/
	}
	
	game->clean(); //gets rid off everything when we close the game

	return 0;
}
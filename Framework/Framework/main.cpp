#include "Game.h"
#include <enet\enet.h>
#include "LevelEditor.h"
Game* game = nullptr;
Lua* lua = nullptr;

int main(int argc, char* argv[])
{

	//const int FPS = 60;
	//const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	lua = new Lua();

	if (enet_initialize() != 0)
	{
		std::cout << "Enet failed to initialise!" << "\n\n";
	}

	/* Much of this will be familiar from the server code. What differs
	is the inclusion of an Peer. This is basically ENet's way of tracking
	what you're connected to. Since our Client will be initialising the
	connection, they need a peer to store information about the server they're
	connecting to. */


	lua_State* F = lua->initLuaFile("level.lua"); // init which lua file I want
	LuaRef t = lua->getLuaGlobal(F, "window"); // get the top index of the lua table I want to read
	LuaRef title = lua->getLuaValue(t, "title"); // get title from the lua file and assign it to LuaRef title
	LuaRef w = lua->getLuaValue(t, "width");
	LuaRef h = lua->getLuaValue(t, "height");

	std::string titleString = title.cast<std::string>();
	int width = w.cast<int>();
	int height = h.cast<int>();

	ENetAddress address;
	ENetHost* client;
	ENetPeer* peer;
	ENetEvent enetEvent;

	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		std::cout << "Client failed to initialise!" << "\n\n";
	}

	enet_address_set_host(&address, "localhost");
	address.port = 1234;

	/* Now we're trying to connect to the server. We include who we are,
	the address to establish the connection to, the number of channels, and a
	generic data variable we can use to say something to the server (currently 0). */

	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL) {
		std::cout << "No available peers for initializing an ENet connection.\n";
	}

	game->init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false); //Initialises the engine and sets parameters for the window

	while (game->running()) //The game order
	{

		frameStart = SDL_GetTicks();  //Sets frame start to how many seconds its been since we initialised SDL

		while (enet_host_service(client, &enetEvent, 0) > 0) // connecting to the server bit 
		{
			switch (enetEvent.type) {

			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Packet received!\n";
				break;
			}
		}

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
	enet_host_destroy(client);
	atexit(enet_deinitialize);

	game->clean(); //gets rid off everything when we close the game

	return 0;
}
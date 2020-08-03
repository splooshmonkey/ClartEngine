#include "Game.h"
#include <enet\enet.h>
#include "LevelEditor.h"
#include <fmod_studio.hpp>
#include <fmod.hpp>


Game* game = nullptr;
Lua* lua = nullptr;

int main(int argc, char* argv[])
{

	//const int FPS = 60;
	//const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	
	/*								lua references start here								*/
	game = new Game();
	lua = new Lua();

	lua_State* F = lua->initLuaFile("level.lua"); // init which lua file I want
	LuaRef t = lua->getLuaGlobal(F, "window"); // get the top index of the lua stack I want to read
	LuaRef title = lua->getLuaValue(t, "title"); // get title from the lua file and assign it to LuaRef title
	LuaRef w = lua->getLuaValue(t, "width");
	LuaRef h = lua->getLuaValue(t, "height");

	std::string titleString = title.cast<std::string>();
	int width = w.cast<int>();
	int height = h.cast<int>();

	/*								FMOD audio code starts here								*/
	FMOD::Studio::System* system = NULL; //initialises a pointer to a studio system
	FMOD::Studio::System::create(&system); //calls a create function

	if (system) {	//check to see if the system got created
		std::cout << "High-level (fmod studio) audio system created." << "\n";
	}

	FMOD::System* lowLevelSystem = NULL; //creates a FMOD system pointer
	system->getLowLevelSystem(&lowLevelSystem); //binds it to the studio system

	if (lowLevelSystem) { //another check
		std::cout << "Low-level (fmod) audio system created." << "\n";
	}

	lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0); //sets speaker mode to stereo
	system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL); //intialises the studio system

	FMOD::Sound* music = NULL; //creates a sound pointer for my music

	lowLevelSystem->createSound("music.wav", FMOD_LOOP_NORMAL, NULL, &music); //reads in my wav file and binds it to the pointer
	//I used FMOD LOOP NORMAL because my sound is background music and should be played constantly

	if (music) {	//another test
		std::cout << "Sound loaded." << "\n";
	}

	music->setDefaults(16400, 0); //allows us to adjust the sound file with speed and pitch etc.

	FMOD::Channel* backgroundMusicChannel = NULL; //channel pointer for my music
	
	if (enet_initialize() != 0) //initializes enet
	{
		std::cout << "Enet failed to initialise!" << "\n\n";
	}

	/*								Enet code starts here									*/
	ENetAddress address;
	ENetHost* client;
	ENetPeer* peer; //tracks what we are connecting to
	ENetEvent enetEvent;

	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		std::cout << "Client failed to initialise!" << "\n\n";
	}

	enet_address_set_host(&address, "localhost");
	address.port = 1234;


	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL) {
		std::cout << "No available peers for initializing an ENet connection.\n";
	}


	/*								Initialises main game loop							*/

	game->init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false); //Initialises the engine and sets parameters for the window

	while (game->running()) //The game order
	{

		frameStart = SDL_GetTicks();  //Sets frame start to how many seconds its been since we initialised SDL

		lowLevelSystem->playSound(music, NULL, false, &backgroundMusicChannel); //plays my music file while the game is running

		while (enet_host_service(client, &enetEvent, 0) > 0) //While we are connected to server and hit the recieve event, cout a message saying so
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
	enet_host_destroy(client); //closes the client instance
	atexit(enet_deinitialize); //deinitializes enet

	game->clean(); //gets rid off everything when we close the game

	return 0;
}
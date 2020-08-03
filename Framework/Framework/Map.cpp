#include "Map.h"
#include "TextureManager.h"
#include "LevelEditor.h"

Lua* luaMap = nullptr;

int level1[20][25] = { //Array we create in the Loadmap function
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,1,1,1,0,1,1,2,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,2,1,1,1,1,0,0,1,1,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,2,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

};



Map::Map()
{

	luaMap = new Lua();
	lua_State* F = luaMap->initLuaFile("level.lua"); //Init which lua file I want
	LuaRef t = luaMap->getLuaGlobal(F, "textures"); //Get the top index of the lua table I want to read
	LuaRef tMud = luaMap->getLuaValue(t, "mud"); //Get mud from the lua file and assign it to LuaRef tMud
	LuaRef tWater = luaMap->getLuaValue(t, "water");
	LuaRef tGrass = luaMap->getLuaValue(t, "grass");

	mud = TextureManager::LoadTexture(tMud);
	water = TextureManager::LoadTexture(tWater);
	grass = TextureManager::LoadTexture(tGrass);

	LoadMap(level1);

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;
}

void Map::LoadMap(int arr[20][25])
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::CreateMap()
{
	int type = 0;
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			type = map[row][column];

			dest.x = column * 32;
			dest.y = row * 32;

			switch (type)
			{
			case 0:
				TextureManager::Create(water, src, dest);
				break;
			case 1:
				TextureManager::Create(grass, src, dest);
				break;
			case 2:
				TextureManager::Create(mud, src, dest);
				break;
			}
		}
	}
}
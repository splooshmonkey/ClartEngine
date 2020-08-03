#pragma once

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <LuaBridge\LuaBridge.h>

using namespace luabridge;

class Lua 
{
public:

	Lua();
	~Lua();

	lua_State* initLuaFile(const char* luaFileName); //init a lua file
	LuaRef getLuaGlobal(lua_State* luaFileRef, const char* luaGlobal); //get the top index of a table
	LuaRef Lua::getLuaValue(LuaRef luaGlobal, const char* luaValueToGet); //access values within a table

private:


};

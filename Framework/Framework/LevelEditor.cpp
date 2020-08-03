#include "LevelEditor.h"


Lua::Lua() {

}

lua_State* Lua::initLuaFile(const char* luaFileName) { //Opening the specific lua file and setting it up to interact with
	lua_State* F = luaL_newstate();
	luaL_dofile(F, luaFileName);
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);
	return F;
}

LuaRef Lua::getLuaGlobal(lua_State* luaFileRef, const char* luaGlobal) { //gets the top index of the stack
	return getGlobal(luaFileRef, luaGlobal); //luaFileRef is passing in a reference to the lua file and getGlobal is the name of the stack we want to access
}

LuaRef Lua::getLuaValue(LuaRef luaGlobal, const char* luaValueToGet) { //luaGlobal is a lua reference to the stack name, luaValueToGet is the value we are interested in getting
	return luaGlobal[luaValueToGet];
}
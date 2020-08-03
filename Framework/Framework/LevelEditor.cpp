#include "LevelEditor.h"


Lua::Lua() {

}

lua_State* Lua::initLuaFile(const char* luaFileName) {
	lua_State* F = luaL_newstate();
	luaL_dofile(F, luaFileName);
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);
	return F;
}

LuaRef Lua::getLuaGlobal(lua_State* luaFileRef, const char* luaGlobal) {
	return getGlobal(luaFileRef, luaGlobal);
}

LuaRef Lua::getLuaValue(LuaRef luaGlobal, const char* luaValueToGet) {
	return luaGlobal[luaValueToGet];
}
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <LuaBridge\LuaBridge.h>
}

using namespace luabridge;



lua_State* F = luaL_newstate();
luaL_dofile(F, "level.lua");
luaL_openlibs(F);
lua_pcall(F, 0, 0, 0);

LuaRef t = getGlobal(F, "window");
LuaRef title = t["title"];
LuaRef w = t["width"];
LuaRef h = t["height"];

int width = w.cast<int>();
int height = h.cast<int>();

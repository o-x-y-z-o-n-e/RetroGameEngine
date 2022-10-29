#include "api/rge.h"
#include "core/scripting.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"


//------------------------------------------------------------------------------


int rge_script_init() {

	// TEST
	/*
	lua_State* L = luaL_newstate();

	int r = luaL_dostring(L, "a = 7 + 11");

	if(r == LUA_OK) {
		lua_getglobal(L, "a");
		if(lua_isnumber(L, -1)) {
			int a = (int)lua_tonumber(L, -1);
			rge_log_info("a = %d", a);
		} else {
			rge_log_error("a is not number");
		}
	} else {
		rge_log_error("Lua failed");
	}
	*/
	// TEST

	return 1;
}
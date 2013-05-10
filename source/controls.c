#include <tiny3d.h>
#include <io/pad.h>
#include "lua4ps3.h"

#define lcontrolslib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"

static int controls_read (lua_State *L)
{
	lua4ps3_controls_read();
	return 0;
}

//([n,] BUTTON)
static int controls_pressed (lua_State *L)
{
	int pad = 0;
	int button = luaL_checkint(L, 1);
	if(lua_gettop(L) > 1)
	{
		pad = button;
		button = luaL_checkint(L, 2);
	}
	lua_pushboolean(L, lua4ps3_paddata[pad].button & button);
	return 1;
}



static const luaL_Reg controlslib[] =
{
	{"read",   controls_read},
	{"pressed",   controls_pressed},
	{NULL, NULL}
};


/*
** Open draw library
*/
LUAMOD_API int luaopen_controls (lua_State *L)
{
	luaL_newlib(L, controlslib);
	lua_setglobal(L, "controls");
	return 1;
}



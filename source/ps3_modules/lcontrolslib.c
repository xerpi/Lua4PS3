#include <io/pad.h>
#include <ya2d/ya2d.h>

#define lcontrolslib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"

static int controls_read (lua_State *L)
{
	ya2d_controlsRead();
	return 0;
}

//([n,] BUTTON)
static int controls_held (lua_State *L)
{
	int pad = 0;
	int button = luaL_checkint(L, 1);
	if(lua_gettop(L) > 1)
	{
		pad = button;
		button = luaL_checkint(L, 2);
	}
	lua_pushboolean(L, ya2d_paddata[pad].BTN_CROSS);
	return 0;
}



static const luaL_Reg controlslib[] =
{
	{"read",   controls_read},
	{"held",   controls_held},
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



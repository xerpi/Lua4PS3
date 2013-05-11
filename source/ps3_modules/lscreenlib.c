#include <tiny3d.h>
#include <libfont.h>
#include <io/pad.h>
#include "screen.h"

#define lscreenlib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"



static int screen_clear (lua_State *L)
{
	/*if(lua_gettop(L) == 0)
	{
		lua_Unsigned color = luaL_checkint(L, 1);
		lua4ps3_screen_set_clear_color(color);
	}*/
	lua4ps3_screen_clear();
	return 0;
}


static int screen_flip (lua_State *L)
{
	lua4ps3_screen_flip();
	return 0;
}

static int screen_begindrawing (lua_State *L)
{
	lua4ps3_screen_begin_drawing();
	return 0;
}

//(x, y, string)
static int screen_print(lua_State *L)
{
	int args = lua_gettop(L);
	if(args < 3)  return luaL_error(L, "wrong number of arguments, expected 3, given %i", args);
	
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	const char *text = luaL_checkstring(L, 3);
	DrawString(x, y, (char *)text);
	return 0;
}



static const luaL_Reg screenlib[] =
{
  {"clear",   screen_clear},
  {"flip",   screen_flip},
  {"begindrawing",   screen_begindrawing},
  {"print",   screen_print},
  {NULL, NULL}
};


/*
** Open screen library
*/
LUAMOD_API int luaopen_screen (lua_State *L)
{
	luaL_newlib(L, screenlib);
	lua_setglobal(L, "screen");
	return 1;
}



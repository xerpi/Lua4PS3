#include <tiny3d.h>
#include <libfont.h>
#include <ya2d/ya2d.h>

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
		ya2d_screenSetClearColor(color);
	}*/
	ya2d_screenClear();
	return 0;
}


static int screen_flip (lua_State *L)
{
	ya2d_screenFlip();
	return 0;
}

static int screen_begindrawing (lua_State *L)
{
	ya2d_screenBeginDrawing();
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

static int screen_fps(lua_State *L)
{
	lua_pushnumber(L, (lua_Number)ya2d_screenFPS());
	return 1;
}



static const luaL_Reg screenlib[] =
{
  {"clear",   screen_clear},
  {"flip",   screen_flip},
  {"begindrawing",   screen_begindrawing},
  {"print",   screen_print},
  {"fps",   screen_fps},
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


